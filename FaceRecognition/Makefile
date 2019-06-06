TARGET = ./main

SRCS := $(wildcard ./src/*.cpp ./*.cpp)

OBJS := $(patsubst %cpp,%o,$(SRCS))

CFLG = -g -Wall -I/usr/local/include -Iinc -I./ -std=c++11

LDFG = -Wl, $(shell pkg-config opencv --cflags --libs)

CXX = clang++

$(TARGET) : $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFG)


%.o:%.cpp
	$(CXX) $(CFLG) -c $< -o $@ 

.PHONY : clean
clean:
	-rm ./*.o
	-rm ./src/*.o