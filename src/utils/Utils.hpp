/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <iostream>
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp> 

class Utils {
    public:
        static std::string generateSocketMessage(std::string str);
        static size_t convertBytesArrayToSizeT(unsigned char *bytes);
};

#endif /* !UTILS_HPP_ */
