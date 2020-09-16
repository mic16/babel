#!/bin/sh

echo "\n\n\e[34m---------------------------------------------\e[39m"
echo "       \e[91m~~~~ Removing useless file ~~~~\e[39m\n"

rm -rf CMakeFiles
rm -rf Makefile
rm -rf CMakeCache.txt
rm -rf cmake_install.cmake
rm -rf babel_client
rm -rf babel_server

echo "            Script is \e[32mFINISHED\e[39m !!!"
echo "\e[35m        -----------------------------\e[39m"
