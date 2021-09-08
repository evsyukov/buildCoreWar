//
// Created by clouise on 29.08.2021.
//
//
//#include "../vm.h"
//
//typedef struct		s_map
//{
//	u8				arena[MEM_SIZE];
//	char			fdf[MEM_SIZE * 2];
//
//} t_map;
//
//int 	choose_color(t_vm *vm, int i)
//{
//	return (vm->movers[i].color);
//}
//
//void	put_in(t_map *map, t_vm *vm, int i,  int color)
//{
//	int next;
//
//	next = i;
//	map->fdf[i * 2 - 1] = (char)(color + 18);
//	if (i == 64)
//		map->fdf[i * 2] = '\n';
//	else
//		map->fdf[i * 2] = ' ';
//}
//
//void	make_map(t_vm *vm)
//{
//	int	i;
//	int	y;
//	int	step;
//	int map[MEM_SIZE];
//
//	i = 0;
//	step = 32;
//	while (i < MEM_SIZE)
//	{
////		ft_printf("%.4p : ", i);
//		y = 0;
//		while (y < step)
//		{
//			put_in(map, vm, i + y,check_movers_colors(vm, i + y));
//			y++;
//		}
//		ft_printf("\n");
//		i += step;
//	}
//}
