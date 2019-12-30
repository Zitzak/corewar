/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 15:26:21 by krioliin       #+#    #+#                */
/*   Updated: 2019/12/30 15:09:11 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm_arena.h"

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
	else
		ft_printf("Arguments are correct!\n");
    if (vm->flag->v)
        visual_corawar();
	vm_free(&vm);
	return (0);
}
