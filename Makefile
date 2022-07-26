# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 16:46:08 by framos-p          #+#    #+#              #
#    Updated: 2022/07/25 17:52:13 by framos-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	get_next_line.a

SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/
CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror -I include
RM 			=	rm -f
AR			=	ar rcs

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRCS_FILES	=	get_next_line get_next_line_bonus get_next_line_utils get_next_line_utils_bonus

SRCS 		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_FILES)))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
DEPS		=	$(addprefix $(OBJS_DIR), $(addsuffix .d, $(SRCS_FILES)))
OBJF		=	.cache_exists

all:
	@${MAKE} ${NAME}


-include ${DEPS}
${NAME}:${OBJS}
	${AR} ${NAME} ${OBJS}
	@echo "$(GREEN)libprintf compiled!$(DEF_COLOR)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJF)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@

${OBJF}:
	@mkdir -p ${OBJS_DIR}

clean:
	@$(RM) -rf $(OBJS_DIR)
	@echo "$(BLUE)libprintf objects files cleaned!$(DEF_COLOR)"

fclean:	clean
	@$(RM) -f $(NAME)
	@echo "$(CYAN)libprintf executable files cleaned!$(DEF_COLOR)"

re:	fclean
	@$(MAKE)
	@echo "$(GREEN)Cleaned and rebuilt everything for libprintf!$(DEF_COLOR)"

norm:
	@norminette ${SRCS} | grep -v Norme -B1 || true;

.PHONY: fclean, all, clean, re
