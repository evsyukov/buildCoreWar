//
// Created by clouise on 18.07.2021.
//

#include "../includes/vm.h"

i32 	from_byte_to_i32(u8 *bytes, size_t size)
{
	i32	i;
	i32 sign;
	i32	i32_code;

	i = 0;
	sign = 0;
	i32_code = 0;
	if (bytes[0] & 0b10000000)
		sign = 1;
	while (size)
	{
		if (sign)
			i32_code += ((bytes[size - 1] ^ 0b11111111) << (i++ * 8));
		else
			i32_code += bytes[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		i32_code = ~(i32_code);
	return (i32_code);
}

i32 	read_i32(t_vm *vm)
{
	i32	ret;
	u8 	tmp[4];

	ret = read(vm->fd, &tmp, 4);
	if (ret < 0)
		terminate(vm, "Unable to read a file");
	if (ret < 4)
		terminate(vm, "not good byte");
	return(from_byte_to_i32(tmp, 4));
}

char	*read_str(t_vm *vm, i32 size)
{
	int		ret;
	char	*buff;

	if (!(buff = ft_strnew(size)))
		terminate(vm, "No mem");
	ret = read(vm->fd, buff, size);
	if (ret < 0)
	{
		free(buff);
		terminate(vm, "Unable read file");
	}
	if (ret < size)
	{
		free(buff);
		terminate(vm, "Wrong file type");
	}
	return (buff);
}


u8 		*read_code(t_vm *vm)
{
	int	ret;
	u8 	*tmp;
	u8 	byte;

	if (!(tmp = malloc(vm->players[vm->i].size)))
		terminate(vm, "Code memory allocation failed");
	ret = read(vm->fd, tmp, vm->players[vm->i].size);
	if (ret < 0)
	{
		free(tmp);
		terminate(vm, "Unable to read code");
	}
	if (ret < vm->players[vm->i].size || read(vm->fd, &byte, 1) != 0)
	{
		free(tmp);
		terminate(vm, "Wrong code size");
	}
	return (tmp);
}

void	read_players(t_vm *vm, i32 player_index)
{
	t_player	player;

	init_player(&player, vm->i);
	vm->initiated_players++;
	vm->players[vm->i] = player;
	if ((vm->fd = open(vm->player_name[player_index], O_RDONLY)) == -1)
		terminate(vm, "Unable read a file");
	if (read_i32(vm) != COREWAR_EXEC_MAGIC) // 0?
		terminate(vm, "One of Magic headers is broken");
	vm->players[vm->i].name = read_str(vm, PROG_NAME_LENGTH);
	if (read_i32(vm) != 0)
		terminate(vm, "File doesn't have control bytes");
	vm->players[vm->i].size = read_i32(vm);
	if (vm->players[vm->i].size < 0)
		terminate(vm, "Player's code is too small");
	if (vm->players[vm->i].size > CHAMP_MAX_SIZE)
		terminate(vm, "Player's code is too big");
	vm->players[vm->i].comment = read_str(vm, COMMENT_LENGTH);
	if (read_i32(vm) != 0)
		terminate(vm, "File doesn't have control bytes");
	vm->players[vm->i].code = read_code(vm);
}
