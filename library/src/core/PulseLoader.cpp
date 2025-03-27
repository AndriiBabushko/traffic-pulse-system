//
// Created by andrii on 3/20/25.
//
#include "core/PulseLoader.h"
#include <pugixml.hpp>
#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <utility>

#include "core/PulseDataManager.h"
#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "types/PulsePosition.h"
#include "types/PulseEvent.h"

namespace {
    int g_next_road_id = 1;
}

// TODO: refactor this into a separate utility class
/**
 * @brief Helper to count the number of child nodes that match a certain predicate.
 */
template <typename Pred>
static int count_children_if(const pugi::xml_node& parent, const char* child_name, Pred pred) {
    int count = 0;
    for (auto node : parent.children(child_name)) {
        if (pred(node)) {
            count++;
        }
    }
    return count;
}

PulseLoader::PulseLoader(PulseDataManager& data_manager, std::string net_file, ISubject& subject)
    : m_data_manager(data_manager)
    , m_net_file_path(std::move(net_file))
    , m_subject(subject)
{
}

void PulseLoader::loadNetworkData() const {
    using namespace std;

    // 1) Notify LOADING_START
    PulseEvent start_event;
    start_event.type = PulseEvents::LOADING_START;
    start_event.message = "[PulseLoader] Starting network file load...";
    start_event.data = std::any();
    m_subject.notify(start_event);

    if (!std::filesystem::exists(m_net_file_path)) {
        throw std::runtime_error("[PulseLoader] Network file not found: " + m_net_file_path);
    }
    cout << "[PulseLoader] LOADING_START: Parsing network file: " << m_net_file_path << endl;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(m_net_file_path.c_str());
    if (!result) {
        throw std::runtime_error("Could not parse network file: " + m_net_file_path +
                                 ", error: " + result.description());
    }
    pugi::xml_node net_node = doc.child("net");
    if (!net_node) {
        throw std::runtime_error("No <net> element found in network file.");
    }

    int total_junctions = count_children_if(net_node, "junction", [](pugi::xml_node){return true;});
    int total_tls = count_children_if(net_node, "junction", [](const pugi::xml_node node){
        return std::string(node.attribute("type").as_string("")) == "traffic_light";
    });
    // # of edges (excluding "internal")
    int total_edges = 0;
    for (auto edge_node : net_node.children("edge")) {
        std::string func = edge_node.attribute("function").as_string("");
        if (func != "internal") {
            total_edges++;
        }
    }

    float items_parsed = 0.0f;
    auto total_items  = static_cast<float>(total_junctions + total_tls + total_edges);

    // Helper lambda to notify progress as we parse each item
    auto notify_progress = [&](const std::string& msg) {
        PulseEvent progress_event;
        progress_event.type = PulseEvents::LOADING_PROGRESS;
        progress_event.message = msg;
        float ratio = items_parsed / total_items;
        progress_event.data = std::any(ratio);
        m_subject.notify(progress_event);
    };

    // ============ PHASE 1: JUNCTIONS ============
    bool found_any_junction = false;
    for (auto jnode : net_node.children("junction")) {
        found_any_junction = true;
        // each iteration => parse one junction
        std::string j_id = jnode.attribute("id").as_string();
        double x = jnode.attribute("x").as_double(0.0);
        double y = jnode.attribute("y").as_double(0.0);

        auto intersection = std::make_unique<PulseIntersection>(j_id, PulsePosition{x, y});
        m_data_manager.addIntersection(std::move(intersection));

        items_parsed += 1.0f;
        notify_progress("Parsing junction: " + j_id);
    }
    if (!found_any_junction) {
        throw std::runtime_error("No <junction> element found in network file.");
    }

    // ============ PHASE 2: TRAFFIC LIGHTS ============
    for (auto jnode : net_node.children("junction")) {
        std::string j_type = jnode.attribute("type").as_string("");
        if (j_type == "traffic_light") {
            std::string tl_id = jnode.attribute("id").as_string();
            auto tl = std::make_unique<PulseTrafficLight>(tl_id);
            m_data_manager.addTrafficLight(std::move(tl));

            items_parsed += 1.0f;
            notify_progress("Parsing traffic light: " + tl_id);
        }
    }

    // ============ PHASE 3: EDGES ============
    for (auto edge_node : net_node.children("edge")) {
        std::string func = edge_node.attribute("function").as_string("");
        if (func == "internal") {
            continue;
        }

        std::string from_id = edge_node.attribute("from").as_string("");
        std::string to_id   = edge_node.attribute("to").as_string("");

        PulseIntersection* from_inter = m_data_manager.getIntersection(from_id);
        PulseIntersection* to_inter   = m_data_manager.getIntersection(to_id);
        if (from_inter && to_inter) {
            double distance = 100.0;
            if (pugi::xml_node lane_node = edge_node.child("lane")) {
                distance = lane_node.attribute("length").as_double(100.0);
            }

            PulseTrafficLight* tl = m_data_manager.getTrafficLight(from_id);
            if (!tl) {
                cout << "[PulseLoader] Warning: No traffic light found for intersection: "
                     << from_id << ". Creating a default one." << endl;
                auto dummy_tl = std::make_unique<PulseTrafficLight>(from_id);
                tl = dummy_tl.get();
                m_data_manager.addTrafficLight(std::move(dummy_tl));
            }
            int road_id = generateRoadID();
            from_inter->addRoadConnection(road_id, to_inter, tl, distance);

            bool is_one_way = edge_node.attribute("oneway").as_bool(false);
            if (!is_one_way) {
                int rev_road_id = generateRoadID();
                PulseTrafficLight* rev_tl = m_data_manager.getTrafficLight(to_id);
                if (!rev_tl) {
                    cout << "[PulseLoader] Warning: No traffic light found for intersection: "
                         << to_id << ". Creating a default one." << endl;
                    auto dummy_rev_tl = std::make_unique<PulseTrafficLight>(to_id);
                    rev_tl = dummy_rev_tl.get();
                    m_data_manager.addTrafficLight(std::move(dummy_rev_tl));
                }
                to_inter->addRoadConnection(rev_road_id, from_inter, rev_tl, distance);
            }
        }

        items_parsed += 1.0f;
        notify_progress("Parsing edge from " + from_id + " to " + to_id);
    }

    cout << "[PulseLoader] Network file parsed successfully." << endl;

    PulseEvent done_event;
    done_event.type = PulseEvents::LOADING_COMPLETE;
    done_event.message = "Network data loading completed!";
    done_event.data = std::any(1.0f);
    m_subject.notify(done_event);
}

int PulseLoader::generateRoadID() {
    return g_next_road_id++;
}
