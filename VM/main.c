/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abumbier <abumbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:26:21 by krioliin          #+#    #+#             */
/*   Updated: 2020/01/18 19:40:50 by abumbier         ###   ########.fr       */
=======
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 15:26:21 by krioliin       #+#    #+#                */
/*   Updated: 2020/01/18 18:24:01 by krioliin      ########   odam.nl         */
>>>>>>> 9a13b64f7be2a8ea4312a9dd078ae53fe1c4dbb5
/*                                                                            */
/* ************************************************************************** */

#include "vm_arena.h"

void	init_vm(t_vm *vm)
{
	vm->process = vm->players_amnt;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->last_alive = vm->players[0]->id;
	vm->cycles_passed = 0;
	vm->current_cycle = 1;
}

/*
**	@desc	- prepares and starts the game
**	@var	- t_vm *vm, main struct holding everything vm needs
*/

int		main(int argc, char **argv)
{
	t_vm		*vm;

	if (!(vm = (t_vm *)ft_memalloc(sizeof(t_vm))))
		return (0);
	if (!(vm->flag = (t_flags *)ft_memalloc(sizeof(t_flags))))
		return (0);
	if (!args_validation(argc, argv, vm->flag))
		parse_error();
	else if (!init_players(vm))
		ft_printf("Can't init players\n");
	else if (!init_battlefield(vm))
	{
		vm_free(&vm);
		return (0);
	}
	else if (!init_cursors(vm))
		ft_printf("Error in cursor init\n");
	else
	{
		init_vm(vm);
		start_game(vm);
	}
	vm_free(&vm);
	return (0);
}
