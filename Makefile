NAME		= a.out

SRCS		= main.cpp

OBJS_PATH	= ./objs/
OBJS_FILES	= ${SRCS:.cpp=.o}
OBJS		= ${patsubst %,${OBJS_PATH}%,${OBJS_FILES}}

INC			= stack vector iterator
INCLUDE		= $(INC:%=-I ./%)

DEPS		= ${OBJS:%.o=%.d}

CXX			= clang++
CXXFLAGS	= -std=c++17 -g3 -fsanitize=address -fsanitize=leak -fsanitize=undefined

RM			= rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${INCLUDE} ${OBJS} -o ${NAME}

${OBJS_PATH}%.o : %.cpp | ${OBJS_PATH}
	${CXX} ${CXXFLAGS} ${INCLUDE} -MMD -MP -c $< -o $@

${OBJS_PATH}:
	mkdir -p ${OBJS_PATH}

-include ${DEPS}

clean:
	${RM} ${OBJS_PATH}

fclean: clean
	${RM} ${NAME}

re: fclean | ${OBJS_PATH} ${NAME}

format:
	clang-format -i $(INC:%= ./%/*)

.PHONY: all clean fclean re format