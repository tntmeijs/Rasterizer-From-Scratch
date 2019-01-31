#!/bin/bash

# Update all submodules for this project
git submodule update --init

# Generate the CMake files for the SFML project
cd _deps/SFML
cmake .

# Back to the root folder
cd ../../

# Perform an out-of-source build to keep the directory clean
rm -rf Build
mkdir Build
cd Build

# Generate project files
cmake ..

# Back to the root folder
cd ../

echo "Installation finished!"
read -p "Press any key to continue..."