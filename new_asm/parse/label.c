/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   label.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 16:16:05 by asulliva       #+#    #+#                */
/*   Updated: 2020/02/17 16:02:33 by abumbier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	@desc	- parses the labels and the instructions
**	@param	- t_asm *data, main struct
**			- char *s, line read
*/

void		parse_label(t_asm *data, char *s)
{
	char	**split;

	data->wfd = 0;
	split = NULL;
	split = ft_strsplit_ws(s);
/* 
	int	i = 0;
	while (split[i])																			//PRINTING instructions
	{
		ft_printf("_%s_", split[i]);
		i++;
	}
	ft_printf("\n");
*/
	if (check_instruction(split[0]))
		parse_instruction(data, split);
	else
	{
		if (!ft_strchr(split[0], LABEL_CHAR))
			error("Not a valid instruction", data->lines);
		else
			get_label(data, split);
	}
	free_arr(NULL, &split, 1);
}
