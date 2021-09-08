//
// Created by clouise on 05.08.2021.
//

# include "../includes/vm.h"

void init_player(t_player *player, i32 num)
{
	player->id = num;
	player->name = NULL;
	player->size = 0;
	player->comment = NULL;
	player->code = NULL;
	player->color = 0;
	player->last = 0;
	player->curr = 0;
	player->prev = 0;
}

i32		get_player_index(t_vm *vm, i32 index)
{
	i32	i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->player_order[i] == index)
			return(i);
	return (-1);
}

int		check_duplicates(t_vm *vm, i32 res)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->player_order[i] == res)
			return (0);
	return (1);
}

i32		find_number(t_vm *vm)
{
	i32 res;
	i32	i;

	res = vm->player_order[0];
	i = -1;
	while (++i < vm->total_players)
		if (vm->player_order[i] < res)
			res = vm->player_order[i];
	res++;
	while (!check_duplicates(vm, res))
		res++;
	return (res);
}

void 	validate_players(t_vm *vm)
{
	i32 player_index;

	vm->i = -1;
	while (++vm->i < vm->total_players) // сортировка порядка игроков
		if (vm->player_order[vm->i] > vm->total_players)
			terminate(vm, "Invalid player number");
		else if (!vm->player_order[vm->i])
			vm->player_order[vm->i] = find_number(vm);
	vm->i = -1;
	while (++vm->i < vm->total_players)
	{
		player_index = get_player_index(vm, vm->i + 1);
		read_players(vm, player_index);
	}
	vm->last_live = vm->total_players;
}
