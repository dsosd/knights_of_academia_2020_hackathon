#!/bin/bash

LD_LIBRARY_PATH=./lib
valgrind --leak-check=full --show-leak-kinds=all ./build/default
