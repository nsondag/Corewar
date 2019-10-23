#include "vm_corewar.h"

void		next_action(t_all *all, t_process *current_process)
{
	if (current_process->wait)
	{
		current_process->wait--;
		return ;
	}
}

int		check_nb_live(t_all *all)
{
	t_process		*process;
	int				i;

	i = -1;
	while (++i < all->stack_proc->n_items)
	{
		if (!(process = (t_process*)ft_array_get(all->stack_proc, i)) &&
			!process->flag_live)
			ft_array_remove(all->stack_proc, i--, NULL);
		else
			process->flag_live = 0;
	}
	return (1);
}

void		vm(t_all *all)
{
	int 	cycle;
	int		i;
	int		total_cycle;

	cycle = 0;
	total_cycle = 0;
	if (!(all->map = malloc(sizeof(char) * MEM_SIZE)))
		print_error_and_exit(MALLOC_ERROR);
	init_vm(all);
	while (all->cycles_before_exit == -1 || total_cycle < all->cycles_before_exit)
	{
		i = 0;
		while (i < all->stack_proc->n_items)
			next_action(all, (t_process*)ft_array_get(all->stack_proc, i++));
		if (cycle++ == all->cycle_to_die)
		{
			if (!check_nb_live(all) || !all->stack_proc->n_items)
				break ;
			if (all->nb_live >= NBR_LIVE  || all->nb_check++ > MAX_CHECKS)
			{
				if ((all->cycle_to_die -= CYCLE_DELTA) <= 0)
					break;
				total_cycle += cycle;
				cycle = 0;
				all->nb_check = 0;
				all->nb_live = 0;
			}
		}
	}
	if (all->last_player_alive)
		ft_printf("le joueur %d(%s) a gagne\n", all->last_player_alive->index, all->last_player_alive->name);
	else
		ft_printf("tout le monde a perdu\n");
}
