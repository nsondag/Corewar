#include "vm_corewar.h"

void    	op_add(t_all *all, t_process *proc)
{
	if (parse_arg_op(all, proc))
	{
		if (proc->op.params[2] >= REG_NUMBER || proc->op.params[2] < 1)
			return ;
		proc->reg[proc->op.params[2] - 1] = proc->reg[proc->op.params[0] - 1] + proc->reg[proc->op.params[1] - 1];
		proc->carry = !proc->reg[proc->op.params[2] - 1];
	}
}
