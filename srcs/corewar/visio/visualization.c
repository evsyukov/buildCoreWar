//
// Created by clouise on 30.08.2021.
//
//
//
//# include "../../includes/vm.h"
//# include <ncurses.h>
//
//
//void	set_colors_map(t_vm *vm) // первичная установка цветов (код который от игроков)
//{
//	int i;
//	int col;
//	int col_prev;
//
//	col = 1;
//	i = 0;
//	col_prev = col;
//	while (i < MEM_SIZE)
//	{
//		if (vm->arena[i] != 0 && vm->maap->old_movers_map[i] != 0)
//		{
//			vm->maap->new_color_map[i] = col;
//			col_prev = col;
//		}
//		else if (vm->arena[i] == 0 && col_prev == col)
//			col++;
//		i++;
//	}
//}
//
//void	set_movers_map(t_vm *vm) // установка цветов на карту кареток
//{
//	int i;
//	int j;
//
//	i = -1;
//	while (++i < MEM_SIZE)
//	{
//		j = 0;
//		while (j < vm->total_movers_alive)
//		{
//			if (i == vm->movers[j].address)
//				vm->maap->new_movers_map[i] = vm->movers[j].color;
//			j++;
//		}
//	}
//}
//
//void fill_olds(t_vm *vm) // заполнение старых значений старых карт новыми
//{
//	int i;
//
//	i = 0;
//	while (i < MEM_SIZE)
//	{
//		vm->maap->old_movers_map[i] = vm->maap->new_movers_map[i];
//		vm->maap->old_color_map[i] = vm->maap->new_color_map[i];
//		i++;
//	}
//}
//
//void init_maap(t_vm *vm)
//{
//	t_maap *new;
//
//	if (!(new = (t_maap *)malloc(sizeof(t_maap))))
//		terminate(vm, "Maap initiation failed");
//	ft_bzero(new->new_color_map, sizeof (int) * MEM_SIZE); // чистим чтобы мусор не попал
//	ft_bzero(new->old_color_map, sizeof (int) * MEM_SIZE);
//	ft_bzero(new->new_movers_map, sizeof (int) * MEM_SIZE);
//	ft_bzero(new->old_movers_map, sizeof (int) * MEM_SIZE);
//	vm->maap = new;
//	set_movers_map(vm);
//	set_colors_map(vm);
//	//fill_olds(vm);
//	//free(new);
//}
//
//void	update_maps(t_vm *vm)
//{
//	int i;
//	int j;
//
//	i = -1;
//	set_movers_map(vm); // установка цветов кареток на карте каректок
//	while (++i < MEM_SIZE)
//	{
//		if (vm->arena[i] != 0 && vm->maap->old_movers_map[i] != 0 &&
//				vm->maap->new_movers_map[i] == 0) // если картека была на месте не пустой ячейки, то дадим ей цвет игрока каретки (без выделений = -10 от цвета выделений)
//		{
//			j = 0; // переменная для учета длины пройденной кареткой, чтобы закрасить промежуток
//			while (vm->maap->new_movers_map[i + j] != vm->maap->old_movers_map[i] && j < MEM_SIZE / 8) // а вот тут возможен глюк если каретка умерла - что-то надо придумать
//			{
//				vm->maap->new_color_map[i + j] = vm->maap->old_movers_map[i] - 10; // если каретка убежала поставить цвет игрока
//				j++;
//			}
//		}
//		else if (vm->arena[i] != 0 && vm->maap->old_color_map[i] != 0)
//			vm->maap->new_color_map[i] = vm->maap->old_color_map[i]; // если цвет был - то оставется (если каретка не перебила его)
//		else
//			vm->maap->new_color_map[i] = 4; // по умолчанию задан в init_colors() как белый на черном фоне
//	}
//
//}
//
//void fill_maaps(t_vm *vm)
//{
//	set_movers_map(vm); // установка карты цвета кареток (можно и потом ее юзать)
//	set_colors_map(vm); // Первоначальная установка цветов полю игроков
//}
//
//int		take_color(t_vm *vm, int i) //взятие цвета для печати
//{
//	if (vm->maap->new_color_map[i] != 0)
//		return (vm->maap->new_color_map[i]);
//	return (5);
//}
//
//void		print_map_visio(t_vm *vm, WINDOW *win)
//{
//	int	i;
//	int	y;
//	int	step;
//	int x;
//	int color;
//
//	y = 0;
//	i = 0;
//	step = 128;
//
//	update_maps(vm); // запись текущих карт цвета на основе предыдущих и арены
//	while (i < MEM_SIZE)
//	{
//		x = 0;
//		while (x < step)
//		{
//			color = COLOR_PAIR(take_color(vm, i + x)); // цвет который должен быть в этой ячейке
//			wattron(win, COLOR_PAIR(color)); // задать аттрибут цвета
//			wprintw(win, "%02x ", vm->arena[i + x]); //печать символа на окно экрана
//
//			wattroff(win, COLOR_PAIR(color)); // сброс аттрибута цвета
//			x++;
//			//x = x + 1;
//		}
//		i += step;
//		y++;
//	}
//	fill_olds(vm); // перенос значений текущих карт цвета в старые
//	ft_bzero(vm->maap->new_color_map, sizeof (int) * MEM_SIZE); // стирание текущих карт цвета
//	ft_bzero(vm->maap->new_movers_map, sizeof (int) * MEM_SIZE);
//
//}
//
//void		init_colors_all() // обозначение цветовых пар для визуализации
//{
//	init_pair(1, COLOR_RED, COLOR_BLACK);
//	init_pair(11, COLOR_WHITE, COLOR_RED);
//	init_pair(2, COLOR_GREEN, COLOR_BLACK);
//	init_pair(12, COLOR_WHITE, COLOR_GREEN);
//	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
//	init_pair(13, COLOR_WHITE, COLOR_YELLOW);
//	init_pair(4, COLOR_BLUE, COLOR_BLACK);
//	init_pair(14, COLOR_WHITE, COLOR_BLUE);
//	init_pair(5, COLOR_WHITE, COLOR_BLACK);
//	init_pair(15, COLOR_BLACK, COLOR_WHITE);
//}
//
//void	put_error_and_exit()
//{
//	fprintf(stderr, "Error initialising ncurses.\n");
//	endwin(); // сброс созданных окон
//	exit(1);
//}
//
//void 	give_colors_begin(t_vm *vm)
//{
//	int i;
//	int color;
//
//	i = 0;
//	color = 1;
//	while (i < vm->total_players)
//	{
//		vm->players[i].color = color;
//		i++;
//		color++;
//	}
//}
//
////t_win	*init_window(int height, int width, int x, int y)
////{
////	t_win	*window;
////
////	window = (t_win *)ft_memalloc(sizeof(t_win));
////	if (!window)
////		put_error_and_exit("Malloc at init_window");
////	window->win = newwin(height, width, y, x);
////	window->height = height;
////	window->width = width;
////	window->x = x;
////	window->y = y;
////	return (window);
////}
//
//int run_visio_vm(t_vm *vm)
//{
//	int width = 130;
//	int height = 130;
//
//	if(!initscr())
//		put_error_and_exit();
//	if(has_colors() == FALSE) // на случай, если нет поддержки цветов терминалом
//	{
//		endwin();
//		printf("Your terminal does not support color\n");
//		exit(1);
//	}
//	start_color();
////	cbreak();
////	int offsetx = (COLS - width) / 2;
////	int offsety = (LINES - height) / 2;
//
//	WINDOW *win = newwin(height, width, 1, 1); // создание структуры окна ncurses
//	box(win,0,0); // рамка для окна (чет не работает)
//
//	init_colors_all(); // включаем цвета
//	give_colors_begin(vm); // назначаем цвета игрокам (плеерам)
//	launch_movers(vm); // запуск кареток (при ините каретки копируется цвет с породившего игрока)
//
//	init_maap(vm); // создание стуктуры матриц цветов
//
//	while (vm->total_movers_alive) // пока есть живые каретки
//	{
//		vm->total_cycles++;
//		vm->curr_cycle++;
//		movers_status(vm, 0); // 0 - обход кареток
//		if (vm->ctd < 1 || vm->curr_cycle == vm->ctd) // если время жизни кончилось
//			movers_status(vm, 1); // 1 - убить каретку
////		if (vm->curr_cycle % 100 == 0 || vm->total_players == 1)
//		print_map_visio(vm, win); // вписание в окно терминала значений окна
//		wrefresh(win); // вывод накопленного вписанных значений на окно
//		werase(win); // стирание окна
//	}
//
//	delwin(win); // аналог free но для структуры окна
//	endwin(); // аналог exit но для структуры окна
//}