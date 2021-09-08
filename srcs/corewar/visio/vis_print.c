//
// Created by clouise on 26.08.2021.
//
# include "vm.h"
# include "visio.h"


int		is_vis(t_vm *vm)
{
	if (vm->vis)
	{
		visio(vm);
		return (1);
	}
	return (0);
}