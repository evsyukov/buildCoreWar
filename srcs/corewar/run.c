# include "../includes/vm.h"

void	print_arena(t_vm *vm)
{
	int	i;
	int	j;
	int	step;

	i = 0;
	step = 32;
	if (vm->flag_dump)
		step *= 2;
	while (i < MEM_SIZE)
	{
		if (i != 0)
			printf("%.4p : ", i);
		else
			printf("0x0000 : ");
		j = -1;
		while (++j < step)
			printf("%.2x ", vm->arena[i + j]);
		printf("\n");
		i += step;
	}
}

int		is_dump(t_vm *vm)
{
	if (vm->flag_dump || vm->flag_d)
		if (vm->cycles_dump == vm->total_cycles)
		{
			print_arena(vm);
			return (1);
		}
	return (0);
}

void	init_new_mover(t_vm *vm, int address)
{
	t_mover *mov;

	if (!(mov = (t_mover *) malloc(sizeof(t_mover))))
		terminate(vm, "Process initiation failed");
	mov->id = vm->total_movers;
	mov->color = vm->total_movers + 10; //vm->players[mov->id].color + 10; // color by init
	//printf("mover = %d color = %d\n", mov->id, mov->color);
	mov->carry = 0;
	mov->reg[0] = -(vm->total_movers); // регистр с номером исходного игрока
	mov->address = address;
	mov->address_buffer = 0;
	mov->code = 0;
	mov->args_valid = 1;
	mov->cycles_wait = 0;
	mov->cycle_last_live = 0;
	mov->next = vm->movers;
	vm->movers = mov;
	vm->total_movers_alive++;

}

void	launch_movers(t_vm *vm)
{
	int address;

	address = 0;
	vm->i = -1;
	while (++vm->i < vm->total_players) // инициализация кареток
	{
		vm->total_movers++;
		init_new_mover(vm, address);
		address += MEM_SIZE / vm->total_players;
	}
	vm->i = -1;
	printf("Introducing contestants...\n");
	while (++vm->i < vm->total_players) // приветствие
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			vm->players[vm->i].id + 1, vm->players[vm->i].size,
			vm->players[vm->i].name, vm->players[vm->i].comment);
}

void	run_vm(t_vm *vm)
{
	launch_movers(vm);
//	visio(vm);
	while (vm->total_movers_alive) // пока есть живые каретки
	{

		//printf("movers alive: %d  cycle %d from %d\n", vm->total_movers_alive, vm->curr_cycle, vm->ctd);
		if (is_dump(vm))
			return ;
		vm->total_cycles++;
		vm->curr_cycle++;
		movers_status(vm, 0); // 0 - обход кареток
		if (vm->ctd < 1 || vm->curr_cycle == vm->ctd) // если время жизни кончилось
			movers_status(vm, 1); // 1 - убить каретку
//		if (vm->curr_cycle % 100 == 0 || vm->total_players == 1)
//			visio(vm);
	}

}
