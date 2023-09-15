NAME		= a.out

SRCS		= main.cpp

OBJS_PATH	= ./objs/
OBJS_FILES	= ${SRCS:.cpp=.o}
OBJS		= ${patsubst %,${OBJS_PATH}%,${OBJS_FILES}}

DOCTEST_DIR	= doctest/doctest
INC			= stack vector iterator list Smart_Pointers
INCLUDE		= ${INC:%=-I ./%} ${DOCTEST_DIR:%=-I ./%}

DEPS		= ${OBJS:.o=.d}

CXX			= g++
CXXFLAGS	= -Wall -Wextra -Wpedantic -std=c++17 -g3 #-g -fsanitize=address -fsanitize=leak -fsanitize=undefined

RM			= rm -rf

all: ${NAME}

${NAME}: ${OBJS_PATH} ${OBJS}
	@ ${CXX} ${CXXFLAGS} ${INCLUDE} ${OBJS} -o ${NAME}
	@ valgrind ./${NAME} --no-exitcode=true
	@ ${RM} ${OBJS_PATH} ${NAME}

${OBJS_PATH}%.o : %.cpp
	@ ${CXX} ${CXXFLAGS} ${INCLUDE} -MMD -MP -c $< -o $@

-include ${DEPS}

${OBJS_PATH}:
	@ mkdir -p ${OBJS_PATH}

format:
	clang-format -i $(INC:%= ./%/*) ${SRCS}

.PHONY: all format