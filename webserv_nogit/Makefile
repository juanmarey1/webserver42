NAME = webserv

CC = c++
RM = rm -rf
EC = echo
CFLAGS = -Wall -Wextra -Werror -std=c++98

INCLUDE_DIR = includes
INCLUDE = -I $(INCLUDE_DIR)

SRCS_DIR = srcs/
SRCS_FILES = webserv.cpp server.cpp location.cpp configFile.cpp
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS = $(SRCS:.cpp=.o)


.cpp.o:
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(EC) "$(OBJS) created"
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)
	@$(EC) "$(NAME) created"


clean: 
	@$(RM) $(OBJS)
	@$(EC) "$(OBJS) removed"

fclean: clean
	@$(RM) $(NAME)
	@$(EC) "$(NAME) removed"

re: fclean all

run: all clean


.PHONY: all clean fclean re run
