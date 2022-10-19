#! /bin/bash

BUILD_TYPE="-DCMAKE_BUILD_TYPE=Debug" # default to building debug
CLEAN=0

while getopts co option; do
    case ${option} in
        c)
        CLEAN=1;;        
        o)
        BUILD_OFFLINE="-DBUILD_OFFLINE=ON";;
        *)
        echo -e "USAGE:\n-c - clean \n-o - offline build";;
    esac
done

if [ "${CLEAN}" == "1" ]; then
    echo "-- cleaning"
    cmake --build ./build --target clean
fi

cmake ${BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=install -DBUILD_TESTS=OFF ${BUILD_OFFLINE} -S ./ -B ./build