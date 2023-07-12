SRCS = main.cpp
INCLUDE = -I ./stack/ \
	-I ./vector/ \
	-I ./iterator/

all:
	g++ -std=c++11 ${INCLUDE} ${SRCS}

clean:
	rm -rf a.out