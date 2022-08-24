NAME	=	containers-std
NAME2	=	containers-ft

CC		=	clang++

FLAG	=	-c				\
			-Wall			\
			-Wextra			\
			-Werror			\
			-Wshadow		\
			-std=c++98

SANIT	=	-fsanitize=address

RM		=	@/bin/rm -rf

SDIR	=	srcs/
ODIR	=	objects/
INCLUDE	=	includes/

FILES	=	main.cpp						\
			vector.cpp						\
			map.cpp							\
			stack.cpp						

SRCS	=	$(addprefix $(SDIR), $(FILES))
OBJS	=	$(SRCS:$(SDIR)%.cpp=$(ODIR)%.o)

all: $(NAME) $(NAME2)

$(NAME): $(OBJS)
	$(CC) -DSTD=1 -o $@ $^

$(NAME2): $(OBJS)
	$(CC) -DSTD=0 -o $@ $^

objects/%.o	:	srcs/%.cpp
			@mkdir -p $(ODIR)
			$(CC) -g3 $(FLAG) -I $(INCLUDE) $< -o $@

clean:
	$(RM) $(ODIR)
	$(RM) *-test.txt

fclean: clean
	$(RM) $(NAME) $(NAME2)

re: fclean all

.PHONY: all clean fclean re