SRCS = main.cpp
INCLUDE = -I ./stack/ \
	-I ./vector/

all:
	g++ -std=c++11 ${INCLUDE} ${SRCS}

clean:
	rm -rf a.out