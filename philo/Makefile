# Project Structure
NAME	=	philo
SRCDIR	=	srcs
OBJDIR	=	objs
INCDIR	=	incs

# Utils
RM	=	rm -rf

# Colors

# Compiler Options
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
CINCS	=	-I./$(INCDIR)

# Files
SRCS	:=	philo.c \
			utils.c
OBJS	:=	$(SRCS:.c=.o)
SCRS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@

.PHONY: all clean fclean re
