#!/bin/sh

g++ -Wall -Werror -std=c++17 -g src/*.cpp -o debug/run
./debug/run $1
