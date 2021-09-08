# include "../includes/vm.h"

int		get_type(int8_t arg_type)
{
	if (arg_type == REG_CODE)
		return (T_REG);
	if (arg_type == DIR_CODE)
		return (T_DIR);
	if (arg_type == IND_CODE)
		return (T_IND);
	return (0);
}

void	get_mover_args_types(t_vm *vm, t_mover *mov)
{
	i8		ar;
	t_op	*op;
	int		i;

	op = &g_op[mov->code - 1];
	ar = vm->arena[locate_address(mov->address + 1)]; // get_one_byte()
	if (op->arg_type_code == 0) // if op_live
	{
		mov->args[0] = op->args_types[0];
		return ;
	}
	i = -1;
	while (++i < op->args_total) // проверка типа аргов, рег, дир или инд
		if (i == 0 && !(mov->args[0] = get_type((i8)((ar & 0xC0) >> 6))))
			mov->args_valid = 0;
		else if (i == 1 && !(mov->args[1] = get_type((i8)((ar & 0x30) >> 4))))
			mov->args_valid = 0;
		else if (i == 2 && !(mov->args[2] = get_type((i8)((ar & 0xC) >> 2))))
			mov->args_valid = 0;
}

int		calculate_step(uint8_t arg, t_op *op)
{
	if (arg == T_REG)
		return (T_REG);
	if (arg == T_IND)
		return (IND_SIZE);
	if (arg == T_DIR)
		return (op->tdir_size);
	return (0);
}

void	verify_mover_args_types(t_vm *vm, t_mover *mov)
{
	t_op	*temp;
	int		next;
	int8_t	loc;

	temp = &g_op[mov->code - 1];
	next = mov->address + 1;
	vm->i = -1;
	if (temp->arg_type_code != 0)
		next++;
	while (++vm->i < temp->args_total)
	{
		if (mov->args[vm->i] == T_REG)
		{
			loc = vm->arena[locate_address(next)];
			if (loc < 1 || loc > REG_NUMBER)
				mov->args_valid = 0;
		}
		next += calculate_step(mov->args[vm->i], temp);
	}
	mov->address_buffer = next;
}

void	is_mover_args_valid(t_vm *vm, t_mover *mov)
{
	t_op	*temp;

	get_mover_args_types(vm, mov);
	temp = &g_op[mov->code - 1]; // check_process_args_type()
	vm->i = -1;
	while (++vm->i < temp->args_total)
		if (!(mov->args[vm->i] & temp->args_types[vm->i]))
			mov->args_valid = 0;
	verify_mover_args_types(vm, mov);
}

