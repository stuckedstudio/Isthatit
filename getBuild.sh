#!/bin/bash
path="$(pwd)"
echo working path is $path
cd ..
rm -r -f quick-cpp-builder
git clone --recursive https://github.com/stuckedstudio/quick-cpp-builder.git
cd quick-cpp-builder
chmod +x setup.sh
./setup.sh
cd $path
cp ../quick-cpp-builder/build.o build.o
echo "build.o moved to project folder :)"