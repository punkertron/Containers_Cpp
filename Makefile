NAME		= a.out
SRCS		= main.cpp
OBJS		= ${SRCS:.cpp=.o}
INC			= stack vector iterator
INCLUDE		= $(INC:%=-I ./%)

CXX			= g++
CXXFLAGS	= -std=c++17

RM			= rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${INCLUDE} ${OBJS} -o ${NAME}

%.o:%.cpp
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re