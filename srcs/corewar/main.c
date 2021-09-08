# include "../includes/vm.h"

void	print_usage(void)
{
	printf("Example: ./corewar_help example_1.cor example_2.cor \n");
	printf("Flag -n number sets the number of the next player: ");
	printf("./corewar_help -n 2 example_1.cor \n");
	printf("Flag -dump nbr_cycles at the end of nbr_cycles of executions, ");
	printf("dump the memory on the standard output and quit the game.\n");
}

void	display_winner(t_vm *vm)
{
	int		winner;
	char	*name;

	winner = vm->last_live;
	name = vm->players[winner].name;
	if (!vm->total_movers_alive)
		printf("Player № %d, \"%s\", won!\n", winner + 1, name);
	else
		terminate(vm, "Last mover did not die");
}

void	init_vm(t_vm **vm)
{
	int i;

	i = 0;
	if (!(*vm = (t_vm *)malloc(sizeof(t_vm))))
		terminate(NULL, "VM initiation failed");
	(*vm)->ctd = CYCLE_TO_DIE;
	(*vm)->max_checks = 0;
	(*vm)->nbr_live = 0;
	(*vm)->cycles_dump = 0;
	(*vm)->curr_cycle = 0;
	(*vm)->total_cycles = 0;
	(*vm)->total_players = 0;
	(*vm)->total_movers = 0;
	(*vm)->flag_live = 0;
	(*vm)->flag_dump = 0;
	(*vm)->flag_d = 0;
	(*vm)->total_movers_alive = 0;
	(*vm)->fd = -1;
	(*vm)->i = 0;
	(*vm)->vis = 0;
	while (i < MAX_PLAYERS)
		(*vm)->player_order[i++] = 0;
	(*vm)->movers = NULL;
}

void	init_arena(t_vm *vm)
{
	int	index;
	
	vm->i = -1;
	index = 0;
	ft_bzero(&(vm->arena), MEM_SIZE);
	while (++vm->i < vm->total_players)
	{
		ft_memcpy(&(vm->arena[index]), 
			vm->players[vm->i].code, vm->players[vm->i].size);
		index += MEM_SIZE / vm->total_players;
	}
}

int		main(int ac, char **av)
{
	t_vm *vm;

	if (ac > 1)
	{
		init_vm(&vm);
		validate_arguments(vm, ac, av);
		validate_players(vm);
		init_arena(vm);
		if (vm->vis == 2)
			run_visio_vm(vm);
		else
			run_vm(vm);
		display_winner(vm);
		free_vm(vm);
	}
	else
		print_usage();
	return (0);
}
