NAME = btc

SRCS = main.cpp BitcoinExchange.cpp

OBJS = $(SRCS:.cpp=.o)

CXXFLAGS = -Wall -Wextra -Werror --std=c++98

CXX = c++

${NAME}: $(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
all : ${NAME}
bonus :
clean :
				rm -f ${OBJS}
fclean : clean
				rm -f ${NAME}
re : fclean all