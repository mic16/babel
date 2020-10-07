#!/bin/sh
./clear.sh
echo "\e[34m---------------------------------------------\e[39m"
echo "        Creating \e[93mbuilder\e[39m the project"
echo "\e[35m        ------------------------------\e[39m\n"

mkdir build
cd build

echo "\e[34m---------------------------------------------\e[39m"
echo "        Install \e[93mConan environment\e[39m of the project"
echo "\e[35m        ------------------------------\e[39m\n"

conan install ..

echo "\e[34m---------------------------------------------\e[39m"
echo "        Preparing to \e[93mCMake \e[39mthe project"
echo "\e[35m        ------------------------------\e[39m\n"

cmake .. -G "Unix Makefiles"

cmake –build .

echo "\n\n\e[34m---------------------------------------------\e[39m"
echo "                  \e[93mCMake \e[32mdone\e[39m !\n"
echo "        Preparing to \e[93mcompile\e[39m the project"
echo "\e[35m        --------------------------------\e[39m\n\n"

make

echo "\n\n\e[34m---------------------------------------------\e[39m"
echo "              \e[93mCompilation \e[32mdone\e[39m !\n"
echo "      The bin \e[96mBabel\e[39m has been created\n"

echo "            Script is \e[32mFINISHED\e[39m !!!"
echo "\e[35m        -----------------------------\e[39m"

cd ..
mv build/bin/Babel .
mv build/bin/BabelServer .
mv build/bin/BabelUdp .


echo "./Babel to launch the project"