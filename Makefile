ASM_BIN = asm
COREWAR_BIN = corewar
INCLUDE = $(wildcard include/*.h)
FLAGS = -Wall -Wextra -Werror

HEADERS = -I./include -I./libft

LIBFT_DIR = libft
LIBFT_A = libft.a

ASM_C = asm.c assemble.c checks.c debug.c \
error_manager.c free.c get_bytes.c get_final_str.c \
hash.c inits.c len_arr.c parse.c parse_args.c \
parse_code.c parse_get_token_list.c parse_instr_list.c \
parse_instr_row.c parse_token_list.c token_utils.c utils.c
COREWAR_C = g_ops/add.c g_ops/aff.c g_ops/and.c g_ops/fork.c \
g_ops/ld.c g_ops/live.c g_ops/lld.c g_ops/op_utils.c g_ops/or.c \
g_ops/st.c g_ops/zjmp.c check_movers.c check_movers_utils.c \
main.c read_players.c run.c utils.c validate_arguments.c \
validate_players.c visio/vis_func2.c visio/vis_func3.c \
visio/visualization2.c

SRCS_DIR = srcs

SRCS_ASM_C = $(addprefix asm/,$(ASM_C))
SRCS_COREWAR_C = $(addprefix corewar/,$(COREWAR_C))

SRCS_ASM_OBJS = $(SRCS_ASM_C:.c=.o)
SRCS_COREWAR_OBJS = $(SRCS_COREWAR_C:.c=.o)
OBJS_DIR = objs

OBJS_ASM_PATH   = $(addprefix $(OBJS_DIR)/, $(SRCS_ASM_OBJS))
OBJS_COREWAR_PATH = $(addprefix $(OBJS_DIR)/, $(SRCS_COREWAR_OBJS))

.PHONY: clean fclean all re

all : $(ASM_BIN) $(COREWAR_BIN)

$(ASM_BIN) : make_libft $(OBJS_ASM_PATH)
	@echo "\033[0;96mСборка ASSEMBLER:\033[0;36m"
	$(CC) $(OBJS_ASM_PATH) $(LIBFT_DIR)/$(LIBFT_A) -o $(ASM_BIN)
	@echo "\033[0;90m"

$(COREWAR_BIN) : make_libft $(OBJS_COREWAR_PATH)
	@echo "\033[0;96mСборка COREWAR:\033[0;36m"
	$(CC) $(OBJS_COREWAR_PATH) $(LIBFT_DIR)/$(LIBFT_A) -o $(COREWAR_BIN)
	@echo "\033[0;90m"

make_libft :
	make -C $(LIBFT_DIR)

$(OBJS_DIR)/asm/%.o : $(SRCS_DIR)/asm/%.c $(INCLUDE) | $(OBJS_DIR)
	$(CC) $(FLAGS) $(HEADERS) -o $@ -c $<

$(OBJS_DIR)/corewar/%.o : $(SRCS_DIR)/corewar/%.c $(INCLUDE) | $(OBJS_DIR)
	$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< -lncurses

$(OBJS_DIR) :
	@echo "\033[32mПодготовка папок для объектных файлов:\033[90m"
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/asm
	mkdir -p $(OBJS_DIR)/corewar
	mkdir -p $(OBJS_DIR)/corewar/g_ops
	mkdir -p $(OBJS_DIR)/corewar/visio
	@echo "\033[38;5;17m"

clean :
	$(RM) -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean : clean
	$(RM) -rf $(ASM_BIN)
	$(RM) -rf $(COREWAR_BIN)
	make fclean -C $(LIBFT_DIR)

re : fclean all
