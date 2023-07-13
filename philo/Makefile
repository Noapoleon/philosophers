# Project Structure
NAME	=	philo
SRCDIR	=	srcs
OBJDIR	=	objs
INCDIR	=	incs

# Utils
RM	=	rm -rf

# Colors
COL_FRONT	=	\033[44;37;1m
COL_BACK	=	\033[7m
COL_ERR		=	\033[41;37;1m
COL_OK		=	\033[32;1m
COL_RESET	=	\033[0m

# Compiler Options
#CC		=	cc
CC		=	cc -fsanitize=address
CFLAGS	=	-Wall -Wextra -Werror -MD -pthread
CINCS	=	-I./$(INCDIR)

# Files
SRCS	:=	main.c \
			setup.c \
			threads.c \
			threads2.c \
			threads3.c \
			utils.c \
			utils2.c
OBJS	:=	$(SRCS:.c=.o)
SCRS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
	fi
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@

-include $(OBJS:.o=.d)

norm:
	@echo -e "$(COL_FRONT)                 $(COL_RESET)"
	@echo -e "$(COL_FRONT)  SOURCES NORM:  $(COL_BACK)  $(COL_RESET)"
	@echo -e "$(COL_FRONT)                 $(COL_BACK)  $(COL_RESET)"
	@echo -e " $(COL_BACK)                  $(COL_RESET)"
	@norminette $(SRCDIR) | awk '{if ($$NF == "OK!") { print "$(COL_OK)"$$0"$(COL_RESET)" } else if ($$NF == "Error!") { print "$(COL_ERR)"$$0"$(COL_RESET)" } else { print }}'
	@echo -e "\n"
	@echo -e "$(COL_FRONT)                  $(COL_RESET)"
	@echo -e "$(COL_FRONT)  INCLUDES NORM:  $(COL_BACK)  $(COL_RESET)"
	@echo -e "$(COL_FRONT)                  $(COL_BACK)  $(COL_RESET)"
	@echo -e " $(COL_BACK)                   $(COL_RESET)"
	@norminette $(INCDIR) | awk '{if ($$NF == "OK!") { print "$(COL_OK)"$$0"$(COL_RESET)" } else if ($$NF == "Error!") { print "$(COL_ERR)"$$0"$(COL_RESET)" } else { print }}'

.PHONY: all clean fclean re norm
