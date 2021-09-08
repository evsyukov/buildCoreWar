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

void		op_aff(t_vm *vm, t_mover *mover)
{
	int		address;
	i8		reg_number;
	i32		reg_value;

	address = mover->address + 2;
	reg_number = vm->arena[locate_address(address)];
	reg_value = mover->reg[reg_number - 1];
	printf("Aff - %c\n", (char)reg_value);
}
