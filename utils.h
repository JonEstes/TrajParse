// Joshua Lequieu, Drexel University, 2020

#ifndef UTILS_H
#define UTILS_H

//std libraries
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>
#include <numeric>      // std::iota
#include <algorithm>    // std::sort, std::stable_sort
#include <sstream>
//external includes 
//OpenFTS includes

// This method holds code that should really live somewhere else, but I didn't want to figure it out at this time, so I just dumped the code here. As is, it is funcitonal, but I would love to find each of these functions a more elegant home

namespace ofts { //FIXME not sure what to call these namespaces

inline void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    elems.clear(); //empty elems
    while (std::getline(ss, item, delim)) {
        if (!item.empty()) //ignore empty entries
          elems.push_back(item);
    }   
}

inline std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


} // namespace
#endif
