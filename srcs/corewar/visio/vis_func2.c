//
// Created by clouise on 26.08.2021.
//

# include "../../includes/vm.h"
# include "../../includes/libft.h"

//# include "visio.h"

//#define home() 			printf(ESC "[H") //Move cursor to the indicated row, column (origin at 1,1)
//#define clrscr()		printf(ESC "[2J") //lear the screen, move to (1,1)
//#define gotoxy(x,y)		printf(ESC "[%d;%dH", y, x);
//#define visible_cursor() printf(ESC "[?251");
///*
//Set Display Attribute Mode	<ESC>[{attr1};...;{attrn}m
//*/
//#define resetcolor() printf(ESC "[0m")
//#define set_display_atrib(color) 	printf(ESC "[%dm",color)

void	home()
{
	printf(ESC"[H"); //Move cursor to the indicated row, column (origin at 1,1)
}
void	ft_clrscr()
{
	printf(ESC"[2J"); //lear the screen, move to (1,1)
}
void	ft_gotoxy(int x,int y)
{
	printf(ESC"[%d;%dH", y, x);
}
void	visible_cursor()
{
	printf(ESC"[?251");
}

void	set_display_atrib(int color)
{
	printf(ESC"[%dm", color);
}
void	ft_resetcolor()
{
	printf(ESC"[0m");
}

void print_winner (t_vm *vm, int find)
{
	home();
	ft_gotoxy(0,24);
	if (find == 0)
	{
		set_display_atrib(BRIGHT);
		set_display_atrib(B_RED);
		printf(" ┌───────────────────────┐\n │ PROCESS IN PROGRESS   │\n"
			   "└───────────────────────┘\n");
		ft_resetcolor();
	}
	else
	{
		set_display_atrib(BRIGHT);
		set_display_atrib(B_GREEN);
		printf("┌───────────────────────┐\n│ %s WINS! │\n└───────────"
			   "────────────┘\n"  , vm->players[vm->last_live - 1].name);
		ft_resetcolor();
	}
//	ft_resetcolor();
	//printf("\n");
}

void frame_draw()
{
	home();
	set_display_atrib(F_BLUE);
//	ft_gotoxy(2, 3);

//            123456789012345678901234567890
	puts(	"┌────────────┐┌─────────┐\n" //0
				  "│movers_alive││         │\n" //1
				  "│curr_cycle  ││         │\n" //2
				  "│max_checks  ││         │\n" //3
				  "│            ││         │\n" //4
				  "│total_movers││         │\n" //5
				  "│total_cycles││         │\n" //6
				  "│            ││         │\n" //7
				  "│nbr_live    ││         │\n" //8
				  "└────────────┘└─────────┘\n" //9
				  "┌───────────────────────┐\n" //10
				  "│                       │\n" //11
				  "└───────────────────────┘\n");  //12
	ft_resetcolor();
}

void print_params(t_vm *vm)
{
	home();
	int x = 1;
	int y = 1;

	set_display_atrib(BRIGHT);
	set_display_atrib(F_YELLOW);
	printf(	"┌────────────┐┌────────────\n"); //0
	ft_gotoxy(x, y);
	printf("│movers_alive││    %i      \n", vm->total_movers_alive);
	ft_gotoxy(x,y + 1);
	printf("│curr_cycle  ││    %i      \n", vm->curr_cycle);
	ft_gotoxy(x,y + 5);
	printf("│total_cycles││    %i      \n", vm->total_cycles);
	ft_gotoxy(x,y + 7);
	printf("│nbr_live    ││    %i      \n", vm->nbr_live);
	ft_gotoxy(x, y + 4);
	printf("│total_movers││    %i      \n", vm->total_movers);
	ft_gotoxy(x,y + 2);
	printf("│max_checks  ││    %i      \n", vm->max_checks);
	printf("└────────────┘└─────────────\n");
	//print_winner(vm);
	ft_resetcolor();
}



int		check_movers_colors(t_vm *vm, i32 addr)
{
	int i;

	i = 0;
//	while (i < vm->total_movers_alive)
//	{
//		if (addr == vm->movers[i].address)
//			return (vm->movers[i].color);
//		i++;
//	}
//	while (i > 0)
//	{
//		if (vm->movers[i].address == addr)
//			return (vm->movers[i].color);
//		i--;
//	}
	return (5);
}

void		print_arena_vis(t_vm *vm)
{
	int	i;
	int	y;
	int	step;

	i = 0;
	step = 64;
//	if (vm->vision == 1)
//		step = 128;
	while (i < MEM_SIZE)
	{
//		printf("%.4p : ", i);
		y = 0;
		while (y < step)
		{
			//set_display_atrib(print_mover(vm, i + y));
//			if (vm->arena[i + y] != 0)
//				set_display_atrib(F_BLUE);
			set_display_atrib(check_movers_colors(vm, i + y));
			printf("%.2x ", vm->arena[i + y]);
			ft_resetcolor();
			y++;
		}
		printf("\n");
		i += step;
	}
}

void 	show_status(t_vm *vm, int winner)
{
	home();
	ft_clrscr();
	//frame_draw();
	print_params(vm);
	print_winner(vm, winner);
	ft_resetcolor();
	//ft_gotoxy(35, 1);
}

void 	print_mem(t_vm *vm)
{
	print_arena_vis(vm);
}

void	visio(t_vm *vm)
{
	if (vm->vis != 0)
	{
		if (vm->total_movers_alive > 1)
		{
			if (vm->vis == 1)
				show_status(vm, 0);
			if (vm->vis == 2)
				print_mem(vm);
		}
		if (vm->vis == 1)
			show_status(vm, 1);
		if (vm->vis == 2)
			print_mem(vm);
	}
}