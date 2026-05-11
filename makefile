SRC := $(wildcard src/*.cpp)
ALLSRC := $(wildcard src/*.cpp src/*.h)
serializer:	$(ALLSRC)
	g++ $(SRC) -g -O0 -w  -o serializer
