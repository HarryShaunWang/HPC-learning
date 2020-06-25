TARGET=FYArray.exe

CXX=g++

CFLAGS=-O3 -std=c++11
LDFLAGS=-fopenmp -lgomp

INCLUDE=../include

OBJ=FYStorage.o main.o

$(TARGET):$(OBJ)
	$(CXX) $^ -o $@
	cp $(TARGET) ../

%.o:%.cpp
	$(CXX) $(LDFLAGS) -I $(INCLUDE) -c $(CFLAGS) $< -o $@ 

.PHONY:clean
clean:
	rm *.o -f
