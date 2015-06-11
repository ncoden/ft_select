# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/29 06:56:00 by ncoden            #+#    #+#              #
#    Updated: 2015/06/11 16:20:47 by ncoden           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

# COMPILATION
CC = gcc
CCFLAGS = -Wall -Werror -Wextra

ASM = nasm
ASMFLAGS = -f macho64

LNK = gcc
LNKFLAGS = -ltermcap

# DIRECTORIES
LIBDIR = .
SRCDIR = src
OBJDIR = obj
INCDIR = \
	includes\
	libft/includes

# SOURCES
LIB = \
	libft/libft.a
SRC = \
	main.c\
	init.c\
	list.c\
	cursor.c

# **************************************************************************** #

# ALLOWED EXTENSIONS
EXTENSIONS = .c .s


# **************************************************************************** #

.PHONY: all $(NAME) build clean fclean re dev
.SILENT:

LIBS = $(addprefix $(LIBDIR)/, $(LIB))

SRC := $(filter $(addprefix %, $(EXTENSIONS)), $(SRC))
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SRC))))
OBJS_DIRS = $(sort $(dir $(OBJS)))

INCS_DIRS = $(addsuffix /, $(INCDIR))
INCS_DIRS += $(addsuffix /, $(dir $(LIBS)))
INCS = $(addprefix -I , $(INCS_DIRS))

all: $(NAME)
$(NAME): build $(LIBS) $(OBJS)
	$(LNK) -o $(NAME) $(LIBS) $(OBJS) $(INCS) $(LNKFLAGS)
build:
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJS_DIRS)
clean:
	rm -f $(LIBS)
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

dev: re
	./$(NAME) /*

$(LIBDIR)/%.a:
	make -s -C $(@D)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(INCS) $(CCFLAGS)
$(OBJDIR)/%.o: $(SRCDIR)/%.s
	$(ASM) -o $@ $< $(INCS) $(ASMFLAGS)
