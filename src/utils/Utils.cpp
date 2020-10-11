/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Utils
*/
/** @file */

#include "Utils.hpp"

std::string Utils::generateSocketMessage(std::string str)
{
	std::stringstream ss;

	unsigned char octets[4];
    unsigned long n = str.size();

	octets[0] = (n >> 24) & 0xFF;
	octets[1] = (n >> 16) & 0xFF;
	octets[2] = (n >> 8) & 0xFF;
	octets[3] = n & 0xFF;
	ss << octets[0];
	ss << octets[1];
	ss << octets[2];
	ss << octets[3];
	ss << str;

    return ss.str();
}

size_t Utils::convertBytesArrayToSizeT(unsigned char *bytes)
{
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}