CXX = g++
CXXFLAGS = -std=c++11 -pthread


SRCS := ${wildcard *.hpp}
OBJS := ${SRCS:.hpp=.o}


all: runner
	@echo ""
	@echo "Run the server by calling ./runner"


runner: ${OBJS}


${OBJS}: %.o: %.hpp %.cpp


clean:
	rm -f ${wildcard *.o} runner


.PHONY: all run clean stress
