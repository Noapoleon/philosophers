# Project Structure
NAME	=	philo
SRCDIR	=	srcs
OBJDIR	=	objs
INCDIR	=	incs

# Utils
RM	=	rm -rf

# Colors
COL_FRONT	=	\033[44;97;1m
COL_RESET	=	\033[0m

# Compiler Options
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -MD -pthread
CINCS	=	-I./$(INCDIR)
DEBUG	=	-g3 -gdwarf-4

# Files
SRCS	:=	philo.c \
			setup.c \
			setup2.c \
			threads.c \
			threads2.c \
			utils.c \
			utils2.c
OBJS	:=	$(SRCS:.c=.o)
SCRS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))
INCS	:= 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(DEBUG) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS:.o=.d)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(DEBUG) $(CFLAGS) $(CINCS) -c $< -o $@

-include $(OBJS:.o=.d)

norm:
	@echo "$(COL_FRONT)                 $(COL_RESET)"
	@echo "\033[44;97;1m  SOURCES NORM:  \033[45;97;1m  \033[0m"
	@echo "\033[44;97;1m                 \033[45;97;1m  \033[0m"
	@echo " \033[45;97;1m                  \033[0m"
	@norminette $(SRCDIR) | awk '{if ($$NF == "OK!") { print "\033[0;92m"$$0"\033[0m" } else if ($$NF == "Error!") { print "\033[41;97;5;1m"$$0"\033[0m" } else { print }}'
	@echo "\n"
	@echo "\033[44;97;1m                  \033[0m"
	@echo "\033[44;97;1m  INCLUDES NORM:  \033[45;97;1m  \033[0m"
	@echo "\033[44;97;1m                  \033[45;97;1m  \033[0m"
	@echo " \033[45;97;1m                   \033[0m"
	@norminette $(INCDIR) | awk '{if ($$NF == "OK!") { print "\033[0;92m"$$0"\033[0m" } else if ($$NF == "Error!") { print "\033[41;97;5;1m"$$0"\033[0m" } else { print }}'

.PHONY: all clean fclean re
