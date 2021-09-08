# include "../includes/vm.h"

void 	terminate(t_vm *vm, char *str)
{
	perror(str);
	exit(0);
}

int		add_step(t_op *op, u8 arg)
{
	int x;
	
	x = 0;
	if (arg == T_REG)
		x = T_REG;
	else if (arg == T_IND)
		x = T_IND;
	else if (arg == T_DIR)
		x = T_DIR;
	return (x);
}

int		locate_address(int address)
{
	int x;

	x = address % MEM_SIZE;
	if (x < 0)
		x += MEM_SIZE;
	return (x);
}

t_mover	*duplicate_mover(t_vm *vm, t_mover *mover, int uid)
{
	t_mover	*new;
	int		i;
	
	i = -1;
	if (!(new = (t_mover *)malloc(sizeof(t_mover))))
		terminate(vm, "Mover failed to be initiated");
	while (++i < REG_NUMBER)
		new->reg[i] = mover->reg[i];
	new->id = uid;
	new->carry = mover->carry;
	new->address = 0;
	new->address_buffer = 0;
	new->cycles_wait = 0;
	new->cycle_last_live = mover->cycle_last_live;
	new->code = 0;
	new->args_valid = 1;
	new->color = mover->color;
	new->next = NULL;
	return (new);
}

void	free_vm(t_vm *vm)
{
	t_mover	*temp;

	vm->i = -1;
	while (vm->movers)
	{
		temp = vm->movers->next;
		free(vm->movers);
		vm->movers = temp;
	}
	while (++vm->i < vm->initiated_players)
	{
		if (vm->players[vm->i].name)
			free(vm->players[vm->i].name);
		if (vm->players[vm->i].code)
			free(vm->players[vm->i].code);
		if (vm->players[vm->i].comment)
			free(vm->players[vm->i].comment);
	}
	free(vm);
}