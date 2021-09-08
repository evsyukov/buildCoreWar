#include "asm.h"

static void	free_token(t_token *token)
{
//	free(token->str);
	FCNT(free(token->str));
//	free(token);
	FCNT(free(token));
	token = NULL;
}

static void free_instr_list(t_instr_list *instr_list) {
	t_instr_row	*instr_row;
//	t_arg_list	*arg_list;
//	t_token		*token;
//	t_token		*token_for_del;
	t_instr_row	*instr_row_for_del;

	instr_row = instr_list->begin;
	while (instr_row != NULL) {
		// TO DO выяснить где уже удалено
//		arg_list = &instr_row->arg_list;
//		token = arg_list->begin;
//		while (token != NULL) {
//			token_for_del = token;
//			token = token->next;
//			free_token(token_for_del);
//		}
		instr_row_for_del = instr_row;
		instr_row = instr_row->next;
//		free(instr_row_for_del);
		FCNT(free(instr_row_for_del));
	}
}

static void	free_token_list(t_token_list *token_list)
{
	t_token	*token;
	t_token	*token_for_del;

	token = token_list->begin;
	while (token != NULL)
	{
		token_for_del = token;
		token = token->next;
		free_token(token_for_del);
	}
	token_list->begin = NULL;
	token_list->end = NULL;
}

static void free_asm_arr(t_asm *asm_node) {
	unsigned int	index;

	index = 0;
	while (index < asm_node->len_arr) {
//		free(asm_node->arr[index]);
		FCNT(free(asm_node->arr[index]));
		++index;
	}
//	free(asm_node->arr);
	FCNT(free(asm_node->arr));
}

void	free_asm_node(t_asm *asm_node) {
	// чистка токен листа
	free_token_list(&(asm_node->token_list));
	// чистка хеш-таблицу
	free_hash_table(asm_node->h_table);
	// чистка instr_list
	free_instr_list(&(asm_node->instr_list));
	// чистка arr
	free_asm_arr(asm_node);
	// free(asm_node->hex_code);
	FCNT(free(asm_node->hex_code));
}