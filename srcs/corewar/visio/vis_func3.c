//
// Created by clouise on 26.08.2021.
//

# include "vm.h"
# include "visio.h"

#include <string.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>

void	copy_arena(t_vm *vm)
{

}

//void 	give_colors_begin(t_vm *vm)
//{
//	int i;
//	int color;
//
//	i = 0;
//	color = 31;
//	while (vm->total_players > i)
//	{
//		vm->movers[i].color = color;
//		i++;
//		color++;
//	}
//}

int		print_mover(t_vm *vm, int cell)
{
	int i;
	int color;

	color = 0;
	i = 0;
	while (i < vm->total_movers_alive)
	{
		if (cell == vm->movers[i].address)
		{
			color = vm->movers[i].color;
			break;
			//set_display_atrib(BRIGHT);
			//set_display_atrib(color);
		}
		i++;
	}
	return (color);
}