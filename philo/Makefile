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
CFLAGS	=	-Wall -Wextra -Werror -MD -pthread
CINCS	=	-I./$(INCDIR)

# Files
SRCS	:=	philo.c \
			utils.c \
			tests.c
OBJS	:=	$(SRCS:.c=.o)
SCRS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))
INCS	:= 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS:.o=.d)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
