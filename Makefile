NAME			= containers

CL				= clang++
RM				= rm -rf
CFLAGS			= -std=c++98 -Wall -Wextra -Werror
SAN				= -g3 -fsanitize=address
INC_LINK		= -I.

SRCS			= main.cpp

OBJS			= $(SRCS:.cpp=.o)
DEPS			= $(SRCS:.cpp=.d)

all: $(NAME)
$(NAME):	$(OBJS)
	@$(CL) -o $(NAME) $(CFLAGS) $(OBJS)

san: fclean $(OBJS)
	@$(CL) -o $(NAME) $(CFLAGS) $(SAN) $(OBJS)

%.o: %.cpp
	@$(CL) $(CFLAGS) -MD -c -o $@ $<

clean:
	@$(RM) $(OBJS) $(DEPS)

fclean:			clean
	@$(RM) $(NAME)

re:				fclean all

-include $(DEPS)

.PHONY:			all clean fclean re
