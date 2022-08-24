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
ODIR2	=	objects2/
INCLUDE	=	includes/

FILES	=	main.cpp						\
			vector.cpp						\
			map.cpp							\
			stack.cpp						

SRCS	=	$(addprefix $(SDIR), $(FILES))
OBJS	=	$(SRCS:$(SDIR)%.cpp=$(ODIR)%.o)
OBJS2	=	$(SRCS:$(SDIR)%.cpp=$(ODIR2)%.o)

all: $(NAME) $(NAME2)

$(NAME): $(OBJS)
	$(CC) $(SANIT) -o $@ $^

$(NAME2): $(OBJS2)
	$(CC) $(SANIT) -o $@ $^

objects/%.o	:	srcs/%.cpp
			@mkdir -p $(ODIR)
			$(CC) -g3 $(FLAG) -DSTD=1 -I $(INCLUDE) $< -o $@

objects2/%.o	:	srcs/%.cpp
			@mkdir -p $(ODIR2)
			$(CC) -g3 $(FLAG) -DSTD=0 -I $(INCLUDE) $< -o $@

clean:
	$(RM) $(ODIR) $(ODIR2)
	$(RM) *-test.txt

fclean: clean
	$(RM) $(NAME) $(NAME2)

re: fclean all

.PHONY: all clean fclean re