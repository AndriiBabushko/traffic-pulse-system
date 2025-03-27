//
// Created by andrii on 3/27/25.
//

#pragma once

#ifndef BFSUTILS_H
#define BFSUTILS_H

#include <functional>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

/**
 * @brief Performs a breadth-first search starting from a given root,
 *        using a callback to retrieve neighbors. Returns the visited
 *        nodes in order of visitation.
 *
 * @param root_id The ID of the root node to start BFS from.
 * @param neighbors_of A callback that, given a node ID, returns a list
 *        of adjacent node IDs.
 * @return A vector of node IDs in the order they were visited by BFS.
 */
inline std::vector<std::string> runBFS(
    const std::string& root_id,
    std::function<std::vector<std::string>(const std::string&)> neighbors_of
)
{
    std::vector<std::string> visited_order;
    if (root_id.empty()) {
        return visited_order;
    }

    std::unordered_map<std::string, bool> visited;
    std::queue<std::string> q;

    q.push(root_id);
    visited[root_id] = true;

    while (!q.empty()) {
        auto current_id = q.front();
        q.pop();

        visited_order.push_back(current_id);

        // Get neighbors from the callback
        auto neighbors = neighbors_of(current_id);
        for (const auto& neighbor_id : neighbors) {
            if (!visited[neighbor_id]) {
                visited[neighbor_id] = true;
                q.push(neighbor_id);
            }
        }
    }
    return visited_order;
}

#endif //BFSUTILS_H

