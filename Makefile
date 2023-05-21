NAME 	:= 	ircserv

OPATH 	:= 	.obj_dir

FLAGS 	:= 	-Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3

SRC 	:= 	$(shell find . -name "*.cpp")

HEADER 	:= 	$(shell find . -name "*.hpp")

OBJS 	:= $(addprefix $(OPATH)/,$(SRC:.cpp=.o))

CPP 	:= 	c++

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(FLAGS) $^ -o $@

$(OPATH)/%.o: %.cpp Makefile $(HEADER)
	@mkdir -p $(dir $@)
	$(CPP) $(FLAGS) -c $< -o $@ 

clean:
	@rm -rf $(OPATH) || true

fclean: clean
	@rm $(NAME) || true

re: fclean all

.PHONY: re clean fclean all
