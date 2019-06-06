TARGET = ./main

SRCS := $(wildcard ./src/*.cpp ./*.cpp)

OBJS := $(patsubst %cpp,%o,$(SRCS))

CFLG = -g -Wall -I/usr/local/include -Iinc -I./ -std=c++11

LDFG = -Wl, $(shell pkg-config opencv --cflags --libs) -I.. ./src/dlib/all/source.cpp -I /usr/local/opt/X11/include -L /usr/lib -lpthread -L /usr/X11/lib  -lX11 -L /usr/local/lib -ljpeg -lpng -DDLIB_JPEG_SUPPORT -std=c++11

CXX = clang++

$(TARGET) : $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFG)


%.o:%.cpp
	$(CXX) $(CFLG) -c $< -o $@ 

.PHONY : clean
clean:
	-rm ./*.o
	-rm ./src/*.o