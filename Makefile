TARGET = main
RM = rm -rf
FixPath = $1

CXX = g++

CXXFLAGS = -std=c++20 -Wall -Wextra -g \
-Iinclude \
-IC:/msys64/clang64/include \
$(shell wx-config --cxxflags)

LDFLAGS = $(shell wx-config --libs richtext,core,base) -lsqlite3

SRC = $(wildcard src/*.cpp) $(wildcard src/view/*.cpp) $(wildcard src/model/*.cpp) $(wildcard src/controller/*.cpp) $(wildcard src/classes/*.cpp) $(wildcard src/additionalScripts/*.cpp) $(wildcard src/database/*.cpp) 
OBJ = $(SRC:.cpp=.o) 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(call FixPath, $(OBJ) $(TARGET))

.PHONY: all clean
