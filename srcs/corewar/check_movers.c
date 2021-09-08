# include "../includes/vm.h"

void	is_dead(t_vm *vm, t_mover *dead)
{
	t_mover	*t1;
	t_mover	*t2;
	t_mover	*t3;
	
	if (vm->ctd < 1 || vm->ctd <= (vm->total_cycles - dead->cycle_last_live))
	{	// удаление каретки
		t1 = NULL;
		t2 = vm->movers;
		t3 = vm->movers;
		while (t2)
		{
			if (t2->id == dead->id)
			{
				if (t1 == NULL)
					t3 = t2->next;
				else
					t1->next = t2->next;
				free(t2);
				break ;
			}
			t1 = t2;
			t2 = t2->next;
		}
		vm->movers = t3;
		vm->total_movers_alive--;
	}
}

void	reset(t_vm *vm, t_mover *temp, int flag_player)
{
	if (!flag_player)
	{
		temp->address = locate_address(temp->address_buffer);
		temp->args_valid = 1;
		temp->address_buffer = 0;
		ft_bzero(temp->args, 3);
		return ;
	}
	vm->i = -1;
	while (++vm->i < vm->total_players)
	{
		vm->players[vm->i].prev = vm->players[vm->i].curr;
		vm->players[vm->i].curr = 0;
	}
	vm->nbr_live = 0;
}

t_mover	*update_mover(t_vm *vm, t_mover *temp)
{
	if (!temp)
		return (NULL);
	if (temp->cycles_wait == 0) // при первом запуске каретка еще не знает сколько ждать set_operation()
	{
		temp->code = vm->arena[temp->address]; // заходит на код
		if (temp->code >= 0x01 && temp->code <= 0x10) // считывает ожидание
			temp->cycles_wait = g_op[temp->code - 1].wait_cycles;
		//printf("origin=%d, c_before=%d\n", temp->id, temp->cycle_before);
	}
	if (temp->cycles_wait > 0) // ждет
		temp->cycles_wait--;
	if (temp->cycles_wait == 0) // после ожидания включается
	{
		if (temp->code >= 0x01 && temp->code <= 0x10)
		{
			is_mover_args_valid(vm, temp); // проверяет аргументы операции
			if (temp->args_valid == 1)
				g_op[temp->code - 1].function(vm, temp);
			//printf("\tchecked: valid=%d %d %s\n", temp->args_valid, temp->code, g_op[temp->code - 1].description);
		}
		else // если операции нет, то просто двигается на шаг вперед
			temp->address_buffer = temp->address + 1;
		//printf("code=%d, address=%d\n", temp->code, temp->address);
		reset(vm, temp, 0); // после операции каретка сбрасывает значения
	}
	return (temp);
}

void	movers_status(t_vm *vm, int dead) // check_all_process()
{
	t_mover	*temp;
	t_mover	*nxt;

	temp = vm->movers;
	if (dead)
	{
		while (temp)
		{
			nxt = temp->next; // запомнить адрес следующей каретки
			is_dead(vm, temp); // убить каретку
			temp = nxt;
		}
		vm->max_checks++;
		vm->curr_cycle = 0;
		if (vm->max_checks == MAX_CHECKS || vm->nbr_live >= NBR_LIVE)
		{	
			vm->ctd -= CYCLE_DELTA;	// reduce cycle to die
			vm->max_checks = 0;
		}
		reset(vm, NULL, 1);
	}
	else if (!dead)
		while (update_mover(vm, temp)) // check_process()
			temp = temp->next;
}
