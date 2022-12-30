source = main.cpp noname.cpp interface.cpp

cc = g++

target = parentalgui

libs = `wx-config --cxxflags` `wx-config --libs`

target:
	${cc} ${libs} -std=c++20 -O2 -o ${target} ${source} -Wno-write-strings
