NAME		=	turing_complete

SRCS		=	\
				main.cpp \
				$(addprefix parser/, \
					LexicalParser.cpp \
					Token.cpp \
					Ast.cpp \
				)
				

_OBJS		=	${SRCS:.cpp=.o}
OBJS		=	$(addprefix build/, $(_OBJS))
OBJS_DEPEND	=	${OBJS:.o=.d}

CXX			=	clang++
CXXFLAGS	=   -Wall -Wextra -Werror -std=c++20
INCLUDE		=	-I includes/

all		:	$(NAME)

build/%.o	:	srcs/%.cpp
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CXX) ${CXXFLAGS} -MMD -MF $(@:.o=.d) ${INCLUDE} -c $< -o $@

$(NAME)	:	$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

-include $(OBJS_DEPEND)

clean	:	
	rm -Rf build/

fclean	:	clean
	rm -f ${NAME}

re		:	fclean ${NAME}

run		:	${NAME}
	./${NAME} example.tc

.PHONY	:	all clean fclean re