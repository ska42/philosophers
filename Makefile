# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/19 23:21:49 by lmartin           #+#    #+#              #
#    Updated: 2020/06/30 04:26:33 by lmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## PIMPED MAKEFILE ##

# COLORS #

# This is a minimal set of ANSI/VT100 color codes
_END		=	\x1b[0m
_BOLD		=	\x1b[1m
_UNDER		=	\x1b[4m
_REV		=	\x1b[7m

# Colors
_GREY		=	\x1b[30m
_RED		=	\x1b[31m
_GREEN		=	\x1b[32m
_YELLOW		=	\x1b[33m
_BLUE		=	\x1b[34m
_PURPLE		=	\x1b[35m
_CYAN		=	\x1b[36m
_WHITE		=	\x1b[37m

# Inverted, i.e. colored backgrounds
_IGREY		=	\x1b[40m
_IRED		=	\x1b[41m
_IGREEN		=	\x1b[42m
_IYELLOW	=	\x1b[43m
_IBLUE		=	\x1b[44m
_IPURPLE	=	\x1b[45m
_ICYAN		=	\x1b[46m
_IWHITE		=	\x1b[47m

# **************************************************************************** #

## VARIABLES ##

SRCS		=	./srcs

DIR			=	./

# DELETE #

RM			=	rm -rf

# COMPILED_SOURCES #

PHILO_ONE	=	philo_one

PHILO_TWO	=	philo_two

PHILO_THREE	=	philo_three

# **************************************************************************** #

## RULES ##

all:			$(PHILO_ONE) $(PHILO_TWO) $(PHILO_THREE)

# VARIABLES RULES #

$(PHILO_ONE):		
				@printf	"$(_BLUE)$(_BOLD)$(PHILO_ONE) $(_END)\n"
				@$(MAKE) -C $(SRCS)/$(PHILO_ONE) MAKEFLAGS=
				@cp -rf $(SRCS)/$(PHILO_ONE)/$(PHILO_ONE) $(DIR)/$(PHILO_ONE)

$(PHILO_TWO):	
				@printf	"$(_BLUE)$(_BOLD)$(PHILO_TWO) $(_END)\n"
				@$(MAKE) -C $(SRCS)/$(PHILO_TWO)/ MAKEFLAGS=
				@cp -rf $(SRCS)/$(PHILO_TWO)/$(PHILO_TWO) ./$(PHILO_TWO)

$(PHILO_THREE):	
				@printf	"$(_BLUE)$(_BOLD)$(PHILO_THREE) $(_END)\n"
				@$(MAKE) -C $(SRCS)/$(PHILO_THREE)/ MAKEFLAGS=
				@cp -rf $(SRCS)/$(PHILO_THREE)/$(PHILO_THREE) ./$(PHILO_THREE)

# OBLIGATORY PART #

clean:
				@printf	"$(_BLUE)$(_BOLD)$(PHILO_ONE) $(_END)\n"
				@make clean -C $(SRCS)/$(PHILO_ONE)
				@printf	"$(_BLUE)$(_BOLD)$(PHILO_TWO) $(_END)\n"
				@make clean -C $(SRCS)/$(PHILO_TWO)
				@printf	"$(_BLUE)$(_BOLD)$(PHILO_THREE) $(_END)\n"
				@make clean -C $(SRCS)/$(PHILO_THREE)

fclean:			
				@printf	"$(_BLUE)$(_BOLD)$(PHILO_ONE) $(_END)\n"
				@make fclean -C $(SRCS)/$(PHILO_ONE)
				@printf	"$(_BLUE)$(_BOLD)$(PHILO_TWO) $(_END)\n"
				@make fclean -C $(SRCS)/$(PHILO_TWO)
				@printf	"$(_BLUE)$(_BOLD)$(PHILO_THREE) $(_END)\n"
				@make fclean -C $(SRCS)/$(PHILO_THREE)
				@$(RM) $(PHILO_ONE)
				@$(RM) $(PHILO_TWO)
				@$(RM) $(PHILO_THREE)

re:				fclean all

# NORME #

norm:
				make norm -C $(SRCS)/$(PHILO_ONE)
				make norm -C $(SRCS)/$(PHILO_TWO)
				make norm -C $(SRCS)/$(PHILO_THREE)

# BONUS #

bonus:			all

re_bonus:		fclean bonus

# PHONY #

.PHONY:			all clean fclean re bonus re_bonus philo_one philo_two philo_three
