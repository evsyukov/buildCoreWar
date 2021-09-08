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

void		op_st(t_vm *vm, t_mover *mover)
{
	int		address;
	i8		res_number;
	i32		reg_value;
	i32		t_ind_value;

	//printf("ST\n");
	address = mover->address + 2;
	res_number = vm->arena[locate_address(address)];
	reg_value = mover->reg[res_number - 1];
	address++;
	if (mover->args[1] == T_IND)
	{
		t_ind_value = get_dir(vm, address, IND_SIZE);
		t_ind_value %= IDX_MOD;
		t_ind_value = locate_address(mover->address + t_ind_value);
		set_dir(vm, t_ind_value, reg_value);
	}
	if (mover->args[1] == T_REG)
	{
		res_number = vm->arena[locate_address(address)];
		mover->reg[res_number - 1] = reg_value;
	}
}

void		op_sti(t_vm *vm, t_mover *mover)
{
	i32		arg_1;
	i32		arg_2;
	i32		reg_value;
	int		address;

	//printf("STI\n");
	address = mover->address + 2;
	reg_value = mover->reg[vm->arena[locate_address(address)] - 1];
	address++;
	address = locate_address(address);
	arg_1 = get_i32_arg_2(vm, mover, 1, address);
	address += add_step(&g_op[11 - 1], mover->args[1]);
	arg_2 = get_i32_arg_2(vm, mover, 2, address);
	set_dir(vm, mover->address + ((arg_1 + arg_2) % IDX_MOD), reg_value);
	//printf("\t%d %d %d\n", arg_1, arg_2, reg_value);
}
