NAME		= a.out
SRCS		= main.cpp
OBJS		= ${SRCS:.cpp=.o}
INC			= stack vector iterator
INCLUDE		= $(INC:%=-I ./%)

DEPS		= ${OBJS:%.o=%.d}

CXX			= clang++
CXXFLAGS	= -std=c++17 #-fsanitize=address -fsanitize=leak -fsanitize=undefined

RM			= rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${INCLUDE} ${OBJS} -o ${NAME}

%.o:%.cpp
	${CXX} ${CXXFLAGS} ${INCLUDE} -MMD -c $< -o $@

-include ${DEPS}

clean:
	${RM} ${OBJS} ${DEPS}

fclean: clean
	${RM} ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re