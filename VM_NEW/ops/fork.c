/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 12:20:50 by asulliva       #+#    #+#                */
/*   Updated: 2020/01/23 14:57:52 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm_arena.h"

/*
**	@desc	- function jumps cursor
**	@param	- t_vm *vm, main struct
**			- t_cursor *c, current cursor
**			- t_args *args, arguments
*/

void	zjmp(t_vm *vm, t_cursor *c, t_args *args)
{
	if (c->carry)
		mv_cursor(vm, c, (args->value % IDX_MOD));
}

/*
**	@desc	- function duplicates cursor and places it to a1.value % mod
**	@param	- t_vm *vm, main struct
**			- t_cursor *c, current cursor
**			- t_args *args, arguments
**			- int mod, value to mod by
*/

void	op_fork(t_vm *vm, t_cursor *c, t_args *args, int mod)
{
	t_cursor	*new;

	new = cp_cursor(c, get_index(c->pos, args->value % mod), c->id);
	add_cursor(&CURSORS, new);
	GAME->processes++;
	if (FLAG->v)
		;
}
