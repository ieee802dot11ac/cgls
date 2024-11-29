#!/usr/bin/sh

rm -r obj/* bin/cgls
mkdir -p obj
mkdir -p bin bin/glsl
cp -r glsl/* bin/glsl/
for file in $(find src -name "*.c"); do
		gcc -g -c -o $(printf "obj/%s.o" $(basename $file .c)) $file
done

gcc -lGL -lm -lSDL2 -o bin/cgls obj/*.o
