#include "asm.h"

void	init_token_list(t_token_list *token_list)
{
	token_list->begin = NULL;
	token_list->end = NULL;
}

void	init_instr_row(t_instr_row *instr_row,
					size_t index, size_t counter_byte)
{
	instr_row->instr.code_instr = index + 1;
	instr_row->instr.num_args = NUM_ARGS[index];
	instr_row->instr.set_first_arg = 0;
	instr_row->instr.set_second_arg = 0;
	instr_row->instr.set_third_arg = 0;
	if (NUM_ARGS[index] >= 1)
		instr_row->instr.set_first_arg = SET_FIRST_ARG[index];
	if (NUM_ARGS[index] >= 2)
		instr_row->instr.set_second_arg = SET_SECOND_ARG[index];
	if (NUM_ARGS[index] == 3)
		instr_row->instr.set_third_arg = SET_THIRD_ARG[index];
	instr_row->instr.is_code_types_exist = IS_CODE_TYPES[index];
	instr_row->arg_list.num_args = NUM_ARGS[index];
	instr_row->arg_list.num_bytes = 0;
	instr_row->arg_list.begin = NULL;
	instr_row->arg_list.end = NULL;
	instr_row->num_bytes = 0;
	instr_row->num_begin_byte = counter_byte;
	instr_row->next = NULL;
	instr_row->prev = NULL;
}

void	init_asm(t_asm *asm_node)
{
	asm_node->header.magic = COREWAR_EXEC_MAGIC;
	ft_memset(asm_node->header.prog_name, '\0', PROG_NAME_LENGTH + 1);
	asm_node->header.prog_size = 0;
	ft_memset(asm_node->header.comment, '\0', COMMENT_LENGTH + 1);
	asm_node->set_header = 0;
	asm_node->token_list.begin = NULL;
	asm_node->token_list.end = NULL;
	asm_node->h_table = hash_table_init();
	asm_node->instr_list.num_instrs = 0;
	asm_node->instr_list.num_bytes = 0;
	asm_node->instr_list.begin = NULL;
	asm_node->instr_list.end = NULL;
	asm_node->arr = NULL;
	asm_node->index_arr = 0;
	asm_node->len_arr = 0;
	asm_node->counter_bytes = 0;
	asm_node->len_final_cor = 0;
	asm_node->hex_code = NULL;
}
