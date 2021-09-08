# include "../includes/vm.h"

int	ft_strncmp_postfix(char *str, char *postfix)
{
	int i;
	int p;
	int strl;
	int postl;

	strl = ft_strlen(str);
	postl = ft_strlen(postfix);
	p = 0;
	if ((i = strl - postl) < 0)
		return (1);
	while (str[i])
	{
		if (str[i] != postfix[p])
			return (1);
		i++;
		p++;
	}
	return (0);
}

void	set_dump(t_vm *vm, char *flag, char *next_av, int ac)
{
	int cycle_num;

	if (vm->flag_d || vm->flag_dump || ac < 2)
		terminate(vm, "Doubled or absent dump/d flag");
	else if (!ft_isint(next_av, 0, -1))
		terminate(vm, "Wrong dump/d value");
	if ((cycle_num = ft_atoi(next_av)) < 0)
		terminate(vm, "Dump is less than 0");
	if (!ft_strcmp(flag, "-dump"))
	{
		vm->flag_dump = 1;
		vm->cycles_dump = (int)cycle_num;
	}
	else if (!ft_strcmp(flag, "-d"))
	{
		vm->flag_d = 1;
		vm->cycles_dump = (int)cycle_num;
	}
}

void	set_player_name(t_vm *vm, char *name)
{
	if (vm->total_players == MAX_PLAYERS)
		terminate(vm, "Too many players");
	vm->player_name[vm->total_players] = name;
	vm->total_players++;
}

void	set_player_n(t_vm *vm, int ac, char **av, int i)
{
	int n;
	int j;

	j = -1;
	if (ac - i <= 2)
		terminate(vm, "Wrong -n status");
	else if (!ft_isint(av[i + 1], 0, -1))
		terminate(vm, "-n is not integer");
	else if ((n = ft_atoi(av[i + 1])) < 1)
		terminate(vm, "-n is less than 1");
	else if (n > MAX_PLAYERS || vm->total_players == MAX_PLAYERS)
		terminate(vm, "Too many players");
	while (++j < MAX_PLAYERS)
		if (vm->player_order[j] == n)
			terminate(vm, "Duplicate player number");
	vm->player_order[vm->total_players] = (int)n;
	if (ft_strncmp_postfix(av[i + 2], ".cor"))
		terminate(vm, "Wrong file name");
	set_player_name(vm, av[i + 2]);
}

void	validate_arguments(t_vm *vm, int ac, char **av)
{
	while (++vm->i < ac)
	{
		if (!ft_strncmp_postfix(av[vm->i], ".cor"))
			set_player_name(vm, av[vm->i]); // если расширение правильное, то имя в буфер
		else if (!ft_strcmp(av[vm->i], "-show"))
			vm->flag_live = 1;
		else if (!ft_strcmp(av[vm->i], "-dump") || !ft_strcmp(av[vm->i], "-d"))
		{
			set_dump(vm, av[vm->i], av[vm->i + 1], ac - vm->i);
			vm->i++;
		}
		else if (!ft_strcmp(av[vm->i], "-v"))
			vm->vis = 1;
		else if (!ft_strcmp(av[vm->i], "-v2"))
			vm->vis = 2;
		else if (!ft_strcmp(av[vm->i], "-n"))
		{
			set_player_n(vm, ac, av, vm->i);
			vm->i += 2;
		}
		else
			terminate(vm, "Wrong argument");
	}
	/*int i;
	i = 0;
	while (i < vm->player_total)
		printf("%d %d %s\n", vm->player_total, vm->player_order[i++], vm->player_name[i]);*/
}
