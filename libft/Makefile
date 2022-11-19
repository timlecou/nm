##################################################
#			GLOBAL VARIABLES DEFINITION			 #
##################################################

TARGET = libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c \
		ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_calloc.c \
		ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_split.c ft_atoi.c ft_itoa.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c	ft_putnbr_fd.c \
		btree_apply_infix.c	btree_apply_prefix.c btree_apply_suffix.c \
		btree_create_node.c btree_insert_data.c	btree_search_item.c btree_clear.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstdup.c
SRC += ft_flags.c ft_print_csp.c ft_print_diux.c ft_print_utils.c ft_printf.c # printf
SRC += ft_pow.c ft_sqrt.c ft_abs.c ft_strtol.c ft_strtof.c # math
SRC += opt_parser.c # cmdline arguments parser
SRC += ft_itoa_base.c get_next_line.c ft_free_map.c ft_clearstr.c # utils

OBJDIR = objs/
OBJS = ${addprefix ${OBJDIR}, ${SRC:.c=.o}}

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

##################################################
#			OUTPUT VARIABLES DEFINITION			 #
##################################################

RED = \e[1;31m
GREEN = \e[1;32m
BLUE = \e[1;34m
PURPLE = \e[0;35m
RESET = \e[0;0m

COMPILE = ${GREEN}Compiling${RESET}
BUILD = ${BLUE}Building${RESET}
CLEAN = ${RED}Cleaning${RESET}

##################################################
#				COMPILATION RULES				 #
##################################################

${OBJDIR}%.o: %.c
	@echo "${COMPILE} $<"
	@${CC} ${CFLAGS} -c $< ${INC} -o $@

${TARGET}: ${OBJDIR} ${OBJS}
	@echo "${BUILD} $@"
	@ar -rcs $@ ${OBJS}

${OBJDIR}:
	@mkdir -p ${OBJDIR}

##################################################
#  				   USUAL RULES					 #
##################################################

all: ${TARGET}

clean:
	@echo "${CLEAN} objects"
	${RM} ${OBJDIR}

fclean:	clean
	@echo "${CLEAN} library"
	${RM} ${TARGET}

re: fclean all

.PHONY: all clean fclean re
