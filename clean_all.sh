#!/bin/sh
rm -rf ./build/
rm -rf ./bin/
rm Makefile
rm ./*.make
echo 'Cleaned working directory'
echo 'Run `premake5 gmake2 && make` to regenerate'
