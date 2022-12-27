source = main.cpp noname.cpp

cc = g++

target = parentalgui

libs = `wx-config --cxxflags --libs`

target:
	${cc} ${libs} -std=c++20 -O2 -o ${target} ${source} -Wno-write-strings