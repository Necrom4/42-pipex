# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 13:36:12 by dferreir          #+#    #+#              #
#    Updated: 2023/02/24 10:29:09 by dferreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
GREEN		= \033[0;32m
RED 		= \033[0;31m
BOLD		= \033[1m
NORMAL		= \033[0m
UP 			= \033[A
CUT 		= \033[K

#OUTPUT
NAME		= pipex

#FILES
LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	= ./libft/
LIBFT_HEADS	= $(LIBFT_DIR)incs/

HEADS_LIST	= pipex.h
HEADS_DIR	= ./incs/
HEADS		= $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SRCS_DIR	= ./srcs/
SRCS_FILES	= pipex.c utils.c
BONUS_SRCS_FILES	= pipex_bonus.c heredoc_bonus.c utils.c
SRCS		:= ${addprefix ${SRCS_DIR}, ${SRCS_FILES}}
BONUS_SRCS	:= ${addprefix ${SRCS_DIR}, ${BONUS_SRCS_FILES}}

OBJS_DIR	= ./objs/
OBJS_FILES	:= ${SRCS_FILES:.c=.o}
BONUS_OBJS_FILES	:= ${BONUS_SRCS_FILES:.c=.o}
OBJS		:= ${addprefix ${OBJS_DIR}, ${OBJS_FILES}}
BONUS_OBJS	:= ${addprefix ${OBJS_DIR}, ${BONUS_OBJS_FILES}}

#COMMANDS
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
MKDIR		= mkdir -p
RM			= rm -rf
LIBS		= -lft -L$(LIBFT_DIR)
INCS		= -I$(HEADS_DIR) -I$(LIBFT_HEADS)

all: ${NAME}

#Compile normal executable
${NAME}: ${LIBFT} ${OBJS_DIR} ${OBJS}
	@${CC} -g ${CFLAGS} ${LIBS} ${INCS} ${OBJS} -o ${NAME}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) created and compiled object files"
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)$(NAME)$(NORMAL) is ready"

#Create objects directory
${OBJS_DIR}:
	@${MKDIR} ${OBJS_DIR}

#Compile normals objects
${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@echo "$(RED)[$(BOLD)Compiling$(NORMAL)$(RED)]$(NORMAL) $<$(UP)$(CUT)"
	@${CC} -g ${CFLAGS} ${INCS} -o $@ -c $<

${LIBFT}:
	@make -C ${LIBFT_DIR}

#Clean obj files
clean:
	@make -C ${LIBFT_DIR} clean
	@${RM} ${OBJS_DIR}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) object files deleted"

#Clean objs files and name
fclean:	clean
	@${RM} ${LIBFT}
	@${RM} ${NAME}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)$(NAME)$(NORMAL) deleted"

#valgrind: all
#	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

re: fclean all

bonus: ${LIBFT} ${OBJS_DIR} ${BONUS_OBJS}
	@${CC} ${CFLAGS} ${LIBS} ${INCS} ${BONUS_OBJS} -o ${NAME}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) created and compiled object files"
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)bonus_$(NAME)$(NORMAL) is ready"

.PHONY: all clean fclean re bonus #valgrind
