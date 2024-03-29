# https://misc.flogisoft.com/bash/tip_colors_and_formatting
_BOLD      =\e[1m
_DIM       =\e[2m
_UNDERLINE =\e[4m
_BLINK     =\e[5m
_REVERSE   =\e[7m
_HIDDEN    =\e[8m

# RESET list
_R          =\e[0m
_RBOLD      =\e[21m
_RDIM       =\e[22m
_RUNDERLINE =\e[24m
_RBLINK     =\e[25m
_RREVERSE   =\e[27m
_RHIDDEN    =\e[28m

# Colors
_RED      =\e[91m
_GREEN    =\e[92m
_YELLOW   =\e[93m
_BLUE     =\e[94m
_MAGENTA  =\e[35m
_CYAN     =\e[96m
_WHITE    =\e[97m

# Inverted, i.e. colored backgrounds
_IRED     =\e[101m
_IGREEN   =\e[102m
_IYELLOW  =\e[103m
_IBLUE    =\e[104m
_IMAGENTA =\e[45m
_ICYAN    =\e[106m
_IWHITE   =\e[107m

#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#                                                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#                                                      #+#    #+#              #
#                                                     ###   ########.fr        #
#                                                                              #
#******************************************************************************#

UNAME := $(shell uname)

NAME = webserv

SRC_DIR = ./src
INC_DIR = $(shell find ./includes -type d -name "includes")
OBJ_DIR = obj

SRCS_DIR = $(shell find $(SRC_DIR) -type d)
INCS_DIR = $(shell find $(INC_DIR) -type d)

vpath %.hpp $(INCS_DIR)

SRC = main.cpp
SRC+= utility.cpp

SRC+= ScannerMessage.cpp
SRC+= ScannerStream.cpp ScannerBuffer.cpp
SRC+= Uri.cpp

# http
SRC+= Message.cpp Request.cpp Response.cpp Status.cpp
SRC+= messageBuilder.cpp messageParser.cpp

# web
SRC+= Device.cpp Socket.cpp Server.cpp

# html
SRC+= pageBuilding.cpp

SRC+= ScannerConfig.cpp ServerConfig.cpp ServerBlock.cpp Host.cpp
SRC+= ReturnDirective.cpp Location.cpp Context.cpp

# ft
SRC+= system_error.cpp error_code.cpp

# ft::filesystem
SRC+= filesystem.cpp path.cpp filesystem_error.cpp file_status.cpp
SRC+= directory_entry.cpp directory_iterator.cpp


OBJ = $(addprefix  $(OBJ_DIR)/,$(SRC:%.cpp=%.o))
vpath %.cpp $(SRCS_DIR)

DEP = $(addprefix  $(OBJ_DIR)/,$(SRC:%.cpp=%.d))

LDFLAGS = $(foreach lib, $(LIB_DIR),-L$(lib))  $(foreach lib, $(LIB),-l$(lib))

CXX = clang++
CXXFLAGS  = -Wall -Wextra -Werror -std=c++98 -MMD -MP  -g #-fsanitize=address  -fsanitize=undefined -fstack-protector  
IFLAGS  = $(foreach inc, $(INCS_DIR),-I$(inc))

#OS specific
ifeq ($(UNAME), Darwin)
	# mac
	CXXFLAGS += -D DARWIN
else
	#Linus and others...
	CXXFLAGS += -D LINUX
endif

all: $(NAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(IFLAGS)  -o $@ $(OBJ) $(LDFLAGS)
	@printf "$(_GREEN)Compiled : $(_MAGENTA)$(NAME)$(_R)\n"
	@printf "\nDo $(_CYAN)$(_BOLD)make show$(_R) to debug the Makefile\n"
	@printf "Do $(_RED)$(_BOLD)make debug$(_R) to run tests with lldb\n"
	@printf "Do $(_YELLOW)$(_BOLD)make valgrind$(_R) to run valgrind $(_MAGENTA)(May have falses positives under OSX)$(_R)\n"

run: $(NAME)
	@./$(NAME)

debug:	CXXFLAGS += -g
debug: $(NAME)
	@lldb $(NAME)

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --show-reachable=yes --track-origins=yes --log-file=output_valgrind ./$(NAME) $(ARGS)
	@printf "$(_BOLD)$(_RED)################################################################$(_R)\n"
	@printf "$(_BOLD)$(_RED)##########################  $(_GREEN)Valgrind$(_RED)  ##########################$(_R)\n"
	@printf "$(_BOLD)$(_RED)################################################################$(_R)\n\n"
	@cat output_valgrind

show:
	@printf "$(_MAGENTA)UNAME   :$(_GREEN)  $(UNAME)$(_END)\n"
	@printf "$(_MAGENTA)ARCH    :$(_GREEN)  $(shell uname -p)$(_END)\n\n"
	@printf "$(_CYAN)NAME    :$(_RED)  $(NAME)$(_END)\n\n"
	@printf "$(_CYAN)CXX     :$(_RED)  $(CXX)$(_END)\n"
	@printf "$(_CYAN)CXXFLAGS:$(_RED)  $(CXXFLAGS)$(_END)\n"
	@printf "$(_CYAN)IFLAGS  :$(_RED)  $(IFLAGS)$(_END)\n"
	@printf "$(_CYAN)LDFLAGS :$(_RED)  $(LDFLAGS)$(_END)\n\n"
	@printf "$(_CYAN)SRC_DIR :$(_RED)  $(SRC_DIR)$(_END)\n"
	@printf "$(_CYAN)INC_DIR :$(_RED)  $(INC_DIR)$(_END)\n"
	@printf "$(_CYAN)SRCS_DIR:$(_RED)  $(SRCS_DIR)$(_END)\n"
	@printf "$(_CYAN)INCS_DIR:$(_RED)  $(INCS_DIR)$(_END)\n"
	@printf "$(_CYAN)LIB_DIR :$(_RED)  $(LIB_DIR)$(_END)\n\n"
	@printf "$(_CYAN)SRC     :$(_RED)  $(SRC)$(_END)\n"
	@printf "$(_CYAN)OBJ     :$(_RED)  $(OBJ)$(_END)\n"
	@printf "$(_CYAN)DEP     :$(_RED)  $(DEP)$(_END)\n"

check:
	@$(MAKE) check -C tests ARGS="$(ARGS)"

jest: $(NAME)
	@./webserv > /dev/null 2>&1 &
	@-npm test && true
	@pkill webserv

sanitize:	CXXFLAGS += -fsanitize=address,leak,undefined -fstack-protector 
sanitize: $(NAME)

jest-sanitize:	CXXFLAGS += -fsanitize=address,leak,undefined -fstack-protector 
jest-sanitize: $(NAME)
	@./webserv  &
	@-npm test && true
	@pkill webserv

clean:
	@rm -rf $(OBJ_DIR) output_valgrind
	@printf "$(_RED)Removed :$(_MAGENTA) $(OBJ_DIR)/ $(_MAGENTA)\n"

fclean: clean
	@rm -fr $(NAME) $(DEBUG_EXEC) $(NAME).dSYM/
	@printf "$(_RED)Removed : $(_MAGENTA)./$(NAME), $(NAME).dSYM/$(_R)\n"
	@$(MAKE) fclean -C tests

re: fclean all

-include $(DEP)

.PHONY: all run debug valgrind norminette bonus show check jest jest-sanitize sanitize clean fclean re


#******************************************************************************#
#                                  REMINDER                                    #  
#******************************************************************************# \
                                                                                 \
                                                                                 \
Automatic variables :                                                            \
                                                                                 \
$@ : rule name  target.         			                                     \
                                                                                 \
$^ : The names of all the prerequisites, with spaces between them. For           \
prerequisites which are archive members, only the named member is used.          \
                                                                                 \
$< : The name of the first prerequisite. If the target got its recipe from an    \
implicit rule, this will be the first prerequisite added by the implicit rule.   \
                                                                                 \
$? : The names of all the prerequisites that are newer than the target, with     \
spaces between them. For prerequisites which are archive members, only the       \
named member is used.                                                            \
                                                                                 \
                                                                                 \
source :                                                                         \
https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html      \

#******************************************************************************#
#                                  RESSOURCES                                  #  
#******************************************************************************# \
resources :                                                                      \
https://www.gnu.org/software/make/manual/html_node/index.html#SEC_Contents       \
http://web.mit.edu/gnu/doc/html/make_toc.html#SEC88                              \
https://www3.nd.edu/~zxu2/acms60212-40212/Makefile.pdf                           \
																				 \
																				 \
cpp:																			 \
https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html		 \
																				 \
																				 \
https://codereview.stackexchange.com/questions/2547/makefile-dependency-generation/11109#11109 		\
