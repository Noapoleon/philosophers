# Project Structure
NAME	=	philo_bonus
SRCDIR	=	srcs
OBJDIR	=	objs
INCDIR	=	incs

# Utils
RM	=	rm -rf

# Colors
COL_FRONT	=	\033[44;37;1m
COL_BACK	=	\033[40m
COL_ERR		=	\033[41;37;5;1m
COL_OK		=	\033[32;1m
COL_RESET	=	\033[0m

# Compiler Options
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -MD -pthread
CINCS	=	-I./$(INCDIR)
DEBUG	=	-g3 -gdwarf-4

# Files
SRCS	:=	main_bonus.c \
			setup_bonus.c \
			utils_bonus.c \
			sim_bonus.c \
			states_bonus.c
OBJS	:=	$(SRCS:.c=.o)
SCRS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))
INCS	:= 

all: $(NAME)

bonus: all

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
	@echo "$(COL_FRONT)  SOURCES NORM:  $(COL_BACK)  $(COL_RESET)"
	@echo "$(COL_FRONT)                 $(COL_BACK)  $(COL_RESET)"
	@echo " $(COL_BACK)                  $(COL_RESET)"
	@norminette $(SRCDIR) | awk '{if ($$NF == "OK!") { print "$(COL_OK)"$$0"$(COL_RESET)" } else if ($$NF == "Error!") { print "$(COL_ERR)"$$0"$(COL_RESET)" } else { print }}'
	@echo "\n"
	@echo "$(COL_FRONT)                  $(COL_RESET)"
	@echo "$(COL_FRONT)  INCLUDES NORM:  $(COL_BACK)  $(COL_RESET)"
	@echo "$(COL_FRONT)                  $(COL_BACK)  $(COL_RESET)"
	@echo " $(COL_BACK)                   $(COL_RESET)"
	@norminette $(INCDIR) | awk '{if ($$NF == "OK!") { print "$(COL_OK)"$$0"$(COL_RESET)" } else if ($$NF == "Error!") { print "$(COL_ERR)"$$0"$(COL_RESET)" } else { print }}'

.PHONY: all clean fclean re bonus norm
