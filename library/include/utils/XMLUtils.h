//
// Created by andrii on 3/28/25.
//
#pragma once

#ifndef XMLUTILS_H
#define XMLUTILS_H

#include <pugixml.hpp>

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

#endif //XMLUTILS_H
