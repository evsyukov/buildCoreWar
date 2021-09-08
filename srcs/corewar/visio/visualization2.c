//
// Created by clouise on 30.08.2021.
//


# include "../../includes/vm.h"
# include <ncurses.h>


void	set_colors_map(t_vm *vm) // первичная установка цветов (код который от игроков)
{
	int i;
	size_t j;

	i = 0;
	while (i < vm->total_movers_alive)
	{
		j = -1;
		while (++j < vm->players[i].size)
		{
			vm->color_map[vm->movers[i].address + j] = vm->movers[i].color;
		}
		i++;
	}
}

void	update_maps(t_vm *vm)
{
	i32 i;
	int j;

	i = 0;
	while (++i < MEM_SIZE)
	{
		j = 0;
		while (j < vm->total_movers_alive)
		{
			if (vm->movers[j].address != i)
				if (vm->color_map[i] > 10)
					vm->color_map[i] = (u8)(vm->color_map[i] - 10);
			if (vm->movers[j].address == i)
				vm->color_map[i] = vm->movers[j].color;
			j++;
		}
		i++;
	}
}

int		take_color(t_vm *vm, int i) //взятие цвета для печати
{
	return (vm->color_map[i]);
}

void		print_map_visio(t_vm *vm, WINDOW *win)
{
	int	i;
	int	y;
	int	step;
	int x;
	int color;

	y = 0;
	i = 0;
	step = 128;

	update_maps(vm); // запись текущих карт цвета на основе предыдущих и арены
	while (i < MEM_SIZE)
	{
		x = -1;
		while (++x < step)
		{
			color = take_color(vm, i + x); // цвет который должен быть в этой ячейке
			wattron(win, COLOR_PAIR(color)); //vm->maap->color_map[i])); // задать аттрибут цвета
			mvwprintw(win, y, x, "%.2x ", vm->arena[i + x]); //печать символа на окно экрана

			wattroff(win, COLOR_PAIR(color));//vm->maap->color_map[i])); // сброс аттрибута цвета
		}
		i += step;
		y++;
	}
}

void		init_colors_all() // обозначение цветовых пар для визуализации
{
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(11, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(12, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(13, COLOR_WHITE, COLOR_YELLOW);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(14, COLOR_WHITE, COLOR_BLUE);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(15, COLOR_BLACK, COLOR_WHITE);
}

void	put_error_and_exit()
{
	fprintf(stderr, "Error initialising ncurses.\n");
	endwin(); // сброс созданных окон
	exit(1);
}

void 	give_colors_begin(t_vm *vm)
{
	int i;
	int color;

	i = 0;
	color = 1;
	while (i < vm->total_players)
	{
		vm->players[i].color = color;
		i++;
		color++;
	}
}

int run_visio_vm(t_vm *vm)
{
	int width = 130;
	int height = 130;

	if(!initscr())
		put_error_and_exit();
	if(has_colors() == FALSE) // на случай, если нет поддержки цветов терминалом
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}

	start_color();
	init_colors_all(); // включаем цвета
	give_colors_begin(vm); // назначаем цвета игрокам (плеерам)



	launch_movers(vm); // запуск кареток (при ините каретки копируется цвет с породившего игрока)

	set_colors_map(vm);

	cbreak();

	WINDOW *win = newwin(height, width, 0, 0); // создание структуры окна ncurses
	box(win,0,0); // рамка для окна (чет не работает)

	while (vm->total_movers_alive) // пока есть живые каретки
	{

		vm->total_cycles++;
		vm->curr_cycle++;
		movers_status(vm, 0); // 0 - обход кареток
		if (vm->ctd < 1 || vm->curr_cycle == vm->ctd) // если время жизни кончилось
			movers_status(vm, 1); // 1 - убить каретку

		print_map_visio(vm, win); // вписание в окно терминала значений окна
		wrefresh(win); // вывод накопленного вписанных значений на окно
		werase(win); // стирание окна
	}

	delwin(win); // аналог free но для структуры окна
	endwin(); // аналог exit но для структуры окна
}