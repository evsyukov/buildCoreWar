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

void		op_lld(t_vm *vm, t_mover *mover)
{
	i8		reg_number;
	i32		reg_value;
	int		address;

	address = mover->address + 2;
	if (mover->args[0] == T_DIR)
		reg_value = get_dir(vm, address, DIR_SIZE_4);
	if (mover->args[0] == T_IND)
		reg_value = get_ind(vm, address, mover->address);
	if (reg_value == 0)
		mover->carry = 1;
	else
		mover->carry = 0;
	if (mover->args[0] == T_DIR)
		address += (DIR_SIZE_4);
	if (mover->args[0] == T_IND)
		address += (IND_SIZE);
	reg_number = vm->arena[locate_address(address)];
	mover->reg[reg_number - 1] = reg_value;
}

void		op_lldi(t_vm *vm, t_mover *mover)
{
	i32		arg_1;
	i32		arg_2;
	i8		reg_number;
	i32		res;
	int		address;

	address = mover->address + 2;
	arg_1 = get_i32_arg_2(vm, mover, 0, address);
	address += add_step(&g_op[10 - 1], mover->args[0]);
	arg_2 = get_i32_arg_2(vm, mover, 1, address);
	address += add_step(&g_op[10 - 1], mover->args[1]);
	reg_number = vm->arena[locate_address(address)];
	res = get_dir(vm, mover->address + (arg_1 + arg_2), DIR_SIZE_2);
	mover->reg[reg_number] = res;
}
