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

void		op_and(t_vm *vm, t_mover *mover)
{
	i8		reg_number;
	i32		arg1;
	i32		arg2;
	i32		res;
	int		address;

	//printf("AND\n");
	address = mover->address + 2;
	arg1 = get_i32_arg(vm, mover, 0, address);
	address += add_step(&g_op[6 - 1], mover->args[0]);
	arg2 = get_i32_arg(vm, mover, 1, address);
	address += add_step(&g_op[6 - 1], mover->args[1]);
	reg_number = vm->arena[locate_address(address)];
	res = arg1 & arg2;
	mover->reg[reg_number - 1] = res;
	if (res == 0)
		mover->carry = 1;
	else
		mover->carry = 0;
}
