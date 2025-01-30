SRCS_CLIENT = src/client.c
SRCS_SERVER = src/server.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJS_DIR = obj
OBJS_CLIENT = $(SRCS_CLIENT:src/%.c=$(OBJS_DIR)/%.o)
OBJS_SERVER = $(SRCS_SERVER:src/%.c=$(OBJS_DIR)/%.o)

NAME_CLIENT = client
NAME_SERVER = server

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -Ilibft

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(LIBFT)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

$(OBJS_DIR)/%.o: src/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re
