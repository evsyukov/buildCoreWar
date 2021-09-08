/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:12:27 by hdeckard          #+#    #+#             */
/*   Updated: 2021/01/06 18:25:33 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		op_zjmp(t_vm *vm, t_mover *mover)
{
	i32	value;
	int	current_pc;

	//printf("ZJMP %d\n", mover->id);
	current_pc = mover->address + 1;
	value = get_dir(vm, current_pc, DIR_SIZE_2);
	if (mover->carry)
		mover->address_buffer = locate_address(mover->address + (value % IDX_MOD));
}
