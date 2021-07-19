CC=clang
FLAGS=-Wall -Wextra -Werror
DEBUG=-g3 -fsanitize=leak
INCLUDES= -I includes/

SRC_PATH=./src/
OBJS_SRC_PATH=./src_obj/
TARGET=my_zsh

SRC := $(wildcard $(SRC_PATH)*.c)

SRC_NAMES := $(notdir $(SRC))
SRC_OBJS := $(addprefix $(OBJS_SRC_PATH), $(SRC_NAMES:.c=.o))


all: $(TARGET)

$(TARGET): $(SRC_OBJS)
	@$(CC) $(FLAGS) $(DEBUG) $(INCLUDES) $(SRC_OBJS) -o $@

$(OBJS_SRC_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJS_SRC_PATH)
	@$(CC) $(FLAGS) $(DEBUG) $(INCLUDES) -c $< -o $@

clean:
	@/bin/rm -rf $(OBJS_SRC_PATH)

fclean: clean
	@/bin/rm -rf $(TARGET)

re: fclean $(TARGET)

.PHONY: clean fclean all
