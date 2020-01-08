
#include "vm_arena.h"

bool		op_sub(t_cursor *cursor, t_vm *vm)
{
	if (cursor && vm)
	{
		cursor->reg[vm->arena[cursor->pos + 4] - 1] = 
		cursor->reg[vm->arena[cursor->pos + 3] - 1] - cursor->reg[vm->arena[cursor->pos + 2] - 1];
		ft_printf("subbed %d from %d = %d\n", cursor->reg[vm->arena[cursor->pos + 2] - 1],
		cursor->reg[vm->arena[cursor->pos + 3] - 1], cursor->reg[vm->arena[cursor->pos + 4] - 1]);
		return (true);
	}
	return (false);
}