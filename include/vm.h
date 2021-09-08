#ifndef VM_H
# define VM_H

# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
#include <ncurses.h>
# include "op.h"
# include "visio.h"

# define DIR_SIZE_2 2
# define DIR_SIZE_4 4


#define ESC "\033"

#define LINE_SIZE 64

//Format text
#define RESET 		0
#define BRIGHT 		1
#define DIM			2
#define UNDERSCORE	3
#define BLINK		4
#define REVERSE		5
#define HIDDEN		6

//Foreground Colours (text)

#define F_BLACK 	30
#define F_RED		31
#define F_GREEN		32
#define F_YELLOW	33
#define F_BLUE		34
#define F_MAGENTA 	35
#define F_CYAN		36
#define F_WHITE		37

//Background Colours
#define B_BLACK 	40
#define B_RED		41
#define B_GREEN		42
#define B_YELLOW	44
#define B_BLUE		44
#define B_MAGENTA 	45
#define B_CYAN		46
#define B_WHITE		47


typedef int32_t		i32;
typedef int8_t		i8;
typedef uint32_t	u32;
typedef uint8_t		u8;

//typedef struct	s_win
//{
//	WINDOW		*win;
//	int			width;
//	int			height;
//	int			x;
//	int			y;
//}				t_win;

typedef struct	s_visi
{
//	t_win		*arena;
//	t_win		*info;
//	t_win		*log;
//	t_win		*legend;
	int			ext;
	int			play;
	int			key;
	size_t		freq;
	uint8_t		mov_map[MEM_SIZE];
}				t_visi;

typedef struct		s_maap
{

	int			new_movers_map[MEM_SIZE];
	int			old_movers_map[MEM_SIZE];
}					t_maap;

//typedef struct		s_maap
//{
//	u8 			*color_map;//[MEM_SIZE];
//	u8			*new_movers_map; //[MEM_SIZE];
//	u8			*old_movers_map; //[MEM_SIZE];
//}					t_maap;

typedef struct		s_mover
{
	int				id;
	int				carry;
	i32				address;
	i32				reg[REG_NUMBER];
	u8				code;
	u8				args[3];
	int				args_valid;
	int				address_buffer;
	int				cycles_wait;
	int				cycle_last_live;
	u8				color;
	struct s_mover	*next;
}					t_mover;

typedef struct		s_player
{
	i32				id; // why i32, not int?
	char			*name;
	char			*comment;
	u8				*code;
	size_t			size;
	i32				curr;
	i32				prev;
	i32				last;
	int				color;
}					t_player;

typedef struct	s_vm
{
	u8			arena[MEM_SIZE]; // арена
	t_mover		*movers; // все каретки
	int			nbr_live; // operation live number
	int			max_checks; // die check counter счетчик проверок смертей
	int			total_players; // макс колво игроков players_count
	int			total_cycles; // колво циклов
	int			total_movers; // колво кареток process_id_counter
	int			total_movers_alive; // количество живых кареток processes number
	int			curr_cycle; // текущий цикл
	int			ctd; // конечный цикл
	i32			player_order[MAX_PLAYERS]; // порядок игроков из флага н players number buffer
	char		*player_name[MAX_PLAYERS]; // имена игроков
	t_player	players[MAX_PLAYERS]; // массив игроков
	int			flag_live; // флаг -show
	int			flag_dump; // dump
	int			flag_d; // dump
	int			cycles_dump; // через сколько циклов выгрузить dump
	i32			i; // временная переменная под что угодно
	int			fd; //  фд
	int			last_live; // players_living winner
	int			initiated_players; // players_init_count
	int			vis; // флаг визуализации
	u8 			colors[MEM_SIZE]; // массив цветов
	char 		*vis_buff;
	t_visi 		*visi; // cструктура хранящяя визио инфу
	u8 			color_map[MEM_SIZE];

}				t_vm;

typedef struct	s_op
{
	void		(*function)(t_vm *, t_mover *);
	u8			code;
	char		*name;
	char		*description;
	int			carry;
	int			args_total;
	u8			arg_type_code;
	u8			args_types[3];
	int			tdir_size;
	int			wait_cycles;
}				t_op;

void		terminate(t_vm *vm, char *str);
void		validate_arguments(t_vm *vm, int ac, char **av);
void		run_vm(t_vm *vm);
void		launch_movers(t_vm *vm);
void		movers_status(t_vm *vm, int dead);
void		is_mover_args_valid(t_vm *vm, t_mover *mov);
void		validate_players(t_vm *vm);
void		init_player(t_player *player, i32 num);
void		read_players(t_vm *vm, i32 player_index);
void		free_vm(t_vm *vm);

int			ft_isint(char *str, int sign, int i);
int			ft_isspace(int c);
int			ft_isdigit(int c);
int			ft_strcmp(const char *str, const char *str2);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *s1, const void *s2, size_t n);

int			locate_address(int loc);
int			add_step(t_op *op, u8 arg);
i32			get_dir(t_vm *vm, int pc, int size);
i32			get_ind(t_vm *vm, int current, int pc); // lld
i32			get_i32_arg(t_vm *vm, t_mover *mover, int post, int pc);
i32			get_i32_arg_2(t_vm *vm, t_mover *mover, int post, int pc);
void		set_dir(t_vm *vm, i32 pc, i32 value);
t_mover		*duplicate_mover(t_vm *vm, t_mover *mover, int uid);

void	op_live(t_vm *vm, t_mover *mover);
void	op_ld(t_vm *vm, t_mover *mover);
void	op_st(t_vm *vm, t_mover *mover);
void	op_add(t_vm *vm, t_mover *mover);
void	op_sub(t_vm *vm, t_mover *mover);
void	op_and(t_vm *vm, t_mover *mover);
void	op_or(t_vm *vm, t_mover *mover);
void	op_xor(t_vm *vm, t_mover *mover);
void	op_zjmp(t_vm *vm, t_mover *mover);
void	op_ldi(t_vm *vm, t_mover *mover);
void	op_sti(t_vm *vm, t_mover *mover);
void	op_fork(t_vm *vm, t_mover *mover);
void	op_lld(t_vm *vm, t_mover *mover);
void	op_lldi(t_vm *vm, t_mover *mover);
void	op_lfork(t_vm *vm, t_mover *mover);
void	op_aff(t_vm *vm, t_mover *mover);


// visio
int		is_vis(t_vm *vm);
void	print_arena(t_vm *vm);
void	visio(t_vm *vm);
void	home();
void	ft_clrscr();
void	ft_gotoxy(int x,int y);
void	visible_cursor();
void	ft_resetcolor();
void	set_display_atrib(int color);
void	print_arena_vis(t_vm *vm);
void	print_winner (t_vm *vm, int find);
void 	show_status(t_vm *vm, int winner);
void	frame_draw();
void	print_params(t_vm *vm);
int		print_mover(t_vm *vm, int cell);
void 	give_colors_begin(t_vm *vm);

int		check_movers_colors(t_vm *vm, i32 addr);

int run_visio_vm(t_vm *vm);

// debug funcs

void 	tata(t_vm *vm);
void	set_check_vis_attrib(t_vm *vm);

static struct s_op	g_op[16] = {
	{
		.function = &op_live,
		.code = 0x01,
		.name = "live",
		.description = "alive",
		.carry = 0,
		.args_total = 1,	// колво аргументов
		.arg_type_code = 0,
		.args_types = {T_DIR, 0, 0},
		.tdir_size = 4,
		.wait_cycles = 10
	},
	{
		.function = &op_ld,
		.code = 0x02,
		.name = "ld",
		.description = "load",
		.carry = 1,
		.args_total = 2,
		.arg_type_code = 1,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.tdir_size = 4,
		.wait_cycles = 5
	},
	{
		.function = &op_st,
		.code = 0x03,
		.name = "st",
		.description = "store",
		.carry = 0,
		.args_total = 2,
		.arg_type_code = 1,
		.args_types = {T_REG, T_REG | T_IND, 0},
		.tdir_size = 4,
		.wait_cycles = 5
	},
	{
		.function = &op_add,
		.code = 0x04,
		.name = "add",
		.description = "addition",
		.carry = 1,
		.args_total = 3,
		.arg_type_code = 1,
		.args_types = {T_REG, T_REG, T_REG},
		.tdir_size = 4,
		.wait_cycles = 10
	},
	{
		.function = &op_sub,
		.code = 0x05,
		.name = "sub",
		.description = "subtraction",
		.carry = 1,
		.args_total = 3,
		.arg_type_code = 1,
		.args_types = {T_REG, T_REG, T_REG},
		.tdir_size = 4,
		.wait_cycles = 10
	},
	{
		.function = &op_and,
		.code = 0x06,
		.name = "and",
		.description = "et (and r1, r2, r3  r1&r2  -> r3",
		.carry = 1,
		.args_total = 3,
		.arg_type_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.tdir_size = 4,
		.wait_cycles = 6
	},
	{
		.function = &op_or,
		.code = 0x07,
		.name = "or",
		.description = "ou (or r1, r2, r3  r1|r2 -> r3",
		.carry = 1,
		.args_total = 3,
		.arg_type_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.tdir_size = 4,
		.wait_cycles = 6
	},
	{
		.function = &op_xor,
		.code = 0x08,
		.name = "xor",
		.description = "ou (xor r1, r2, r3  r1^r2 -> r3",
		.carry = 1,
		.args_total = 3,
		.arg_type_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.tdir_size = 4,
		.wait_cycles = 6
	},
	{
		.function = &op_zjmp,
		.code = 0x09,
		.name = "zjmp",
		.description = "jump if zero",
		.carry = 0,
		.args_total = 1,
		.arg_type_code = 0,
		.args_types = {T_DIR, 0, 0},
		.tdir_size = 2,
		.wait_cycles = 20
	},
	{
		.function = &op_ldi,
		.code = 0x0A,
		.name = "ldi",
		.description = "load index",
		.carry = 0,
		.args_total = 3,
		.arg_type_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.tdir_size = 2,
		.wait_cycles = 25
	},
	{
		.function = &op_sti,
		.code =0x0B,
		.name = "sti",
		.description = "store index",
		.carry = 0,
		.args_total = 3,
		.arg_type_code = 1,
		.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.tdir_size = 2,
		.wait_cycles = 25
	},
	{
		.function = &op_fork,
		.code = 0x0C,
		.name = "fork",
		.description = "fork",
		.carry = 0,
		.args_total = 1,
		.arg_type_code = 0,
		.args_types = {T_DIR, 0, 0},
		.tdir_size = 2,
		.wait_cycles = 800
	},
	{
		.function = &op_lld,
		.code = 0x0D,
		.name = "lld",
		.description = "long load",
		.carry = 1,
		.args_total = 2,
		.arg_type_code = 1,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.tdir_size = 4,
		.wait_cycles = 10
	},
	{
		.function = &op_lldi,
		.code = 0x0E,
		.name = "lldi",
		.description = "long load index",
		.carry = 1,
		.args_total = 3,
		.arg_type_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.tdir_size = 2,
		.wait_cycles = 50
	},
	{
		.function = &op_lfork,
		.code = 0x0F,
		.name = "lfork",
		.description = "alive",
		.carry = 0,
		.args_total = 1,
		.arg_type_code = 0,
		.args_types = {T_DIR, 0, 0},
		.tdir_size = 2,
		.wait_cycles = 1000,
	},
	{
		.function = &op_aff,
		.code = 0x10,
		.name = "aff",
		.description = "alive",
		.carry = 0,
		.args_total = 1,
		.arg_type_code = 1,
		.args_types = {T_REG, 0, 0},
		.tdir_size = 4,
		.wait_cycles = 2
	}
};

# endif
