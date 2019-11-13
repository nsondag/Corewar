#include "vm_corewar.h"

void		next_action(t_all *all, t_process *current_process)
{
	if (current_process->wait)
	{
		if (--current_process->wait == 0)
		{
				// if (all->flag & FLAG_VISU)
				// 	//&& !(total_cycle % 20))
				// {
				// 	hexdump_map_square(all);
				// 	usleep(2000);
				// 	moveTo(10, 80 * 3);
				// 	// printf("nb_cycle %d", total_cycle);
				// 	// moveTo(120, 0);
				// }
			current_process->op.op(all, current_process);
			// hexdump_map_square(all);
		}
		return ;
	}
	if ((all->map.character[current_process->pc] < 1 || all->map.character[current_process->pc] > 16))
	{
		move_pc(&current_process->pc, 1);
		// hexdump_map_square(all);	
		return ;
	}
	// if (!(all->flag & FLAG_RESUME))
	// 	printf(""); // phrase pour print l'action dans le terminal
	// hexdump_map_square(all);
	ft_memcpy(&current_process->op, &op_tab[all->map.character[current_process->pc]], sizeof(t_op));
	current_process->wait = current_process->op.cycles - 1;
	// op_tab[all->map.character[current_process->pc]].op(all, current_process);
}

int		check_nb_live(t_all *all)
{
	static int		first_test = 0;
	t_process		*process;
	int				i;

	i = -1;
	while (++i < all->stack_proc->n_items)
	{
		process = (t_process*)ft_array_get(all->stack_proc, i);
		if (!process->flag_live && first_test)
			ft_array_remove(all->stack_proc, i--, NULL);
		else
			process->flag_live = 0;
	}
	first_test = 1;
	return (all->stack_proc->n_items);
}
#include <time.h>
void		vm(t_all *all)
{
	t_all	*tmp_all;
	int 	cycle;
	int		i;
	int		total_cycle;
clock_t time = 0;
	cycle = 0;
	total_cycle = 0;
	
	init_vm(all);
	while (all->cycles_before_exit == -1 || total_cycle < all->cycles_before_exit)
	{
		i = 0;
		if (all->flag & FLAG_VISU && !(total_cycle % 5))
		{
			// if (time + CLOCKS_PER_SEC * 0.01 > clock())
			// 	usleep((time + CLOCKS_PER_SEC * 0.01 - clock()) / (CLOCKS_PER_SEC * 0.000001));
			// while (time + CLOCKS_PER_SEC * 0.01 > clock())
			// 	;
			// time = clock();
			moveTo(10, 64 * 3 + 20);
			printf("nb_cycle %d", total_cycle + 1);
			hexdump_map_square(all);
		}
		tmp_all = all;
		int tmp = all->stack_proc->n_items;
		while (i < tmp)
			next_action(all, (t_process*)ft_array_get(all->stack_proc, i++));
		total_cycle++;
		// printf("cycle %d all->cycle_to_die %d total_cycle %d\n", cycle, all->cycle_to_die, total_cycle);
		if (cycle++ == all->cycle_to_die)
		{
			if (!check_nb_live(all))
				break ;
			if (all->nb_live >= NBR_LIVE  || all->nb_check++ > MAX_CHECKS)
			{
				if ((all->cycle_to_die -= CYCLE_DELTA) <= 0)
					break;
				all->nb_check = 0;
			}
			all->nb_live = 0;
			cycle = 0;
		}
	}
	if (FLAG_DUMP)
		simple_hexdump(all);
	else if (all->last_player_alive)
		ft_printf("le joueur %d(%s) a gagne\n", all->last_player_alive->index, all->last_player_alive->name);
	else
		ft_printf("tout le monde a perdu\n");
	while (all->flag & FLAG_VISU)
		;
}
