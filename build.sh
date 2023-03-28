#!/bin/bash

g++ "$1" -o "$3" -I"$6" -lstdc++ $(find "$2" -name '*.cpp') $(find "$2" -name '*.h' -o -name '*.hpp' -exec echo "-include {}" \;)
