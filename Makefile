NAME	=	exec

CC		=	g++

FLAG	=	-c				\
			-Wall			\
			-Wextra			\
			-Werror			\
			-Wshadow		\
			-Wno-Shadow		\
			-Wfatal-errors	\
			-std=c++98

SANIT	=	-fsanitize=address

RM		=	@/bin/rm -rf

SDIR	=	srcs/
ODIR	=	objects/
INCLUDE	=	includes/

FILES	=	main.cpp

SRCS	=	$(addprefix $(SDIR), $(FILES))
OBJS	=	$(SRCS:$(SDIR)%.cpp=$(ODIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(SANIT) -o $@ $^

objects/%.o	:	srcs/%.cpp
			@mkdir -p $(ODIR)
			$(CC) -g $(FLAG) -I $(INCLUDE) $< -o $@

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re