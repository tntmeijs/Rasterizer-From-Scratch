#!/bin/bash

# Update all submodules for this project
git submodule update --init

# Generate the CMake files for the GLM project
cd _deps/GLM
cmake .

# Back to the _deps folder
cd ../

# Generate the CMake files for the SFML project
cd SFML
cmake .

# Back to the root folder
cd ../../

# Perform an out-of-source build to keep the directory clean
rm -rf build
mkdir build
cd build

# Generate project files
cmake ..

# Back to the root folder
cd ../

echo "Installation finished!"
read -p "Press any key to continue..."