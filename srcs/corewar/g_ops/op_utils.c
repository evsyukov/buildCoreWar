#include "../../includes/vm.h"

i32		get_dir(t_vm *vm, int pc, int size)
{
	i32	format;
	int	sign;
	int	i;
	int	address;

	i = 0;
	sign = 0;
	format = 0;
	address = locate_address(pc);
	if (vm->arena[pc] & 0x80)
		sign = 1;
	while (size)
	{
		pc = locate_address(address + size - 1);
		if (sign)
			format += ((vm->arena[pc] ^ 0xFF) << (i++ * 8));
		else
			format += vm->arena[pc] << (i++ * 8);
		size--;
	}
	if (sign)
		format = ~(format);
	return (format);
}

void	set_dir(t_vm *vm, i32 pc, i32 value)
{
	i8	i;
	int	size;
	int	address;
	
	i = 0;
	size = 4;
	address = locate_address(pc);
	while (size)
	{
		pc = locate_address(address + size - 1);
		vm->arena[pc] = (u8)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

i32		get_ind(t_vm *vm, int current_pc, int pc)
{
	i32	address;
	i32	val;
	
	address = get_dir(vm, current_pc, IND_SIZE);
	address %= IDX_MOD;
	address = locate_address(pc + address);
	val = get_dir(vm, address, REG_SIZE);
	return (val);
}

i32		get_i32_arg(t_vm *vm, t_mover *mover, int pos, int pc)
{
	i32	res;
	int arg;
	
	arg = mover->args[pos];
	if (arg & T_REG)
		res = mover->reg[vm->arena[locate_address(pc)] - 1];
	else if (arg & T_DIR)
		res = get_dir(vm, pc, DIR_SIZE_4);
	else if (arg & T_IND)
		res = get_ind(vm, pc, mover->address);
	return (res);
}

i32		get_i32_arg_2(t_vm *vm, t_mover *mover, int pos, int pc)
{
	i32	res;
	int arg;
	
	arg = mover->args[pos];
	if (arg & T_REG)
		res = mover->reg[vm->arena[locate_address(pc)] - 1];
	else if (arg & T_DIR)
		res = get_dir(vm, pc, DIR_SIZE_2);
	else if (arg & T_IND)
		res = get_ind(vm, pc, mover->address);
	return (res);
}