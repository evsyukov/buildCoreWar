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

void		op_fork(t_vm *vm, t_mover *mover)
{
	i32		arg;
	int		address;
	t_mover	*new;

	//printf("FORK\n");
	address = mover->address + 1;
	arg = get_dir(vm, address, DIR_SIZE_2);
	new = duplicate_mover(vm, mover, ++(vm->total_movers));
	new->address = locate_address(mover->address + (arg % IDX_MOD));
	new->next = vm->movers;
	vm->movers = new;
	vm->total_movers_alive++;
}

void		op_lfork(t_vm *vm, t_mover *mover)
{
	i32		arg;
	int		address;
	t_mover	*new;

	address = mover->address + 1;
	arg = get_dir(vm, address, DIR_SIZE_2);
	new = duplicate_mover(vm, mover, vm->total_movers++);
	new->address = locate_address(mover->address + arg);
	new->next = vm->movers;
	vm->movers = new;
	vm->total_movers_alive++;
}
