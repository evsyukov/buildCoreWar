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

#include "vm.h"

void	op_add(t_vm *vm, t_mover *mover)
{
	i8		r1;
	i8		r2;
	i8		r3;
	i32		res;
	int		address;

	address = mover->address + 2;
	r1 = vm->arena[locate_address(address)];
	address++;
	r2 = vm->arena[locate_address(address)];
	address++;
	r3 = vm->arena[locate_address(address)];
	res = mover->reg[r1 - 1] + mover->reg[r2 - 1];
	mover->reg[r3 - 1] = res;
	if (res == 0)
		mover->carry = 1;
	else
		mover->carry = 0;
}

void		op_sub(t_vm *vm, t_mover *mover)
{
	i8		r1;
	i8		r2;
	i8		r3;
	int		address;
	i32		res;

	address = mover->address + 2;
	r1 = vm->arena[locate_address(address)];
	address++;
	r2 = vm->arena[locate_address(address)];
	address++;
	r3 = vm->arena[locate_address(address)];
	res = mover->reg[r1 - 1] - mover->reg[r2 - 1];
	mover->reg[r3 - 1] = res;
	if (res == 0)
		mover->carry = 1;
	else
		mover->carry = 0;
}
