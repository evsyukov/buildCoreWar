/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:12:27 by hdeckard          #+#    #+#             */
/*   Updated: 2021/01/06 18:25:33 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_live(t_vm *vm, t_mover *mover)
{
	i32		arg;
	int		address;

	address = mover->address + 1;
	//arg = address_from_arena(vm->arena, address, DIR_SIZE_4);
	arg = get_dir(vm, address, DIR_SIZE_4);
	//printf("LIVE %d\taddress/arg: %d/%d\t", mover->id, address, arg);
	if (arg < 0 && arg >= -(vm->total_players))
	{
		arg *= -1;
		vm->players[arg - 1].last = vm->total_cycles;
		vm->players[arg - 1].curr++;
		vm->last_live = vm->players[arg - 1].id;
		//printf("%s\t", vm->players[arg - 1].name);
		if (vm->flag_live == 1)
			printf("A process shows that player %d (%s) is alive”.\n",
				   vm->players[arg - 1].id, vm->players[arg - 1].name);
	}
	vm->nbr_live++;
	mover->cycle_last_live = vm->total_cycles;
	//printf("arg=%d\tlast_live: %d\n", arg, vm->last_live);
}
