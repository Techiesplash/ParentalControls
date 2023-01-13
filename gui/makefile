source = main.cpp noname.cpp ../reusable/reusable.cpp

cc = g++

target = parentalgui

libs = `wx-config --cxxflags` `wx-config --libs`


target:
	${cc} -std=c++20 -O2 -o ${target} ${source} -Wno-write-strings ${libs}
