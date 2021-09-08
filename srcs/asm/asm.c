#include "asm.h"

unsigned long	g_ml = 0;
unsigned long	g_fr = 0;

static void	output_to_cor_file(t_asm *asm_node, char *final_arr, char *file_cor)
{
	int	fd;

	fd = open(file_cor, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error_and_exit();
	// TO DO чек на то что в файл успешно прошла запись
	write(fd, final_arr, asm_node->len_final_cor);
	// TO DO чек на то что файл успешно закрылся
	close(fd);
}

static int	check_extension(char *file_name, char *extention)
{
	unsigned int	len_file_name;
	unsigned int	len_ext;
	unsigned int	index;

	len_file_name = ft_strlen(file_name);
	len_ext = ft_strlen(extention);
	if (len_file_name <= len_ext)
		return (0);
	index = 0;
	while (index < len_ext)
	{
		if (file_name[len_file_name - len_ext + index] != extention[index])
			return (0);
		++index;
	}
	return (1);
}

static int	check_args(int argc, char **argv)
{
	if (argc != 2 || !check_extension(argv[1], ".s"))
		return (0);
	return (1);
}

static void	do_main(char *file_name)
{
	t_asm	asm_node;
	char	*final_arr;
	char	*cor_file_name;

	init_asm(&asm_node);
	parse(&(asm_node.token_list), file_name);
	// Рез-т это создание asm_node.token_list
	// DEBUG
	print_token_list(&(asm_node.token_list));
	// DEBUG
	parse_token_list(&asm_node);
	// Рез-т это
	// 1. заполнение хеш-таблицы (нужно для меток)
	// 2. создание asm_node->instr_list
	parse_instr_list(&asm_node);
	// Рез-т это заполненный asm_node.arr (t_byte** arr)
	// DEBUG
	print_arr(&asm_node);
	// DEBUG
	assemble_arr_hex(&asm_node);
	//  это марезультатссив asm_node.hex_code
	final_arr = get_final_str(&asm_node);
	cor_file_name = get_cor_file_name(file_name);
	output_to_cor_file(&asm_node, final_arr, cor_file_name);

	// очищение памяти
	free_asm_node(&asm_node);
//	free(final_arr);
	FCNT(free(final_arr));
//	free(cor_file_name);
	FCNT(free(cor_file_name));
}

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv))
	{
		ft_putstr("Usage: ./asm filename.s\n");
		return (0);
	}
	do_main(argv[1]);
	// DEBUG
//	do_main("ex.s");
	// DEBUG
	print_malloc_free();
	// DEBUG
	return (0);
}
