CXX=clang++
PLATFLAGS=-m32
CXXFLAGS=-Wall -std=c++11 -stdlib=libc++
OPTFLAGS=-g
EXE=test_parse

all: build

build:
	$(CXX) test_parse.cpp $(PLATFLAGS) $(CXXFLAGS) $(OPTFLAGS) -o $(EXE)
