/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 15:51:26 by asulliva       #+#    #+#                */
/*   Updated: 2020/02/13 16:12:07 by abumbier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	@desc	- function picks which parsing function to call
**	@param	- t_asm *data, main struct
**			- char *s, line read from the file
*/

void		choose_parse(t_asm *data, char *s)
{
	if (s && ft_strlen(s) > 0)
	{
		if (!ft_strncmp(s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			parse_nc(data, s, 0);
		else if (!ft_strncmp(s, COMMENT_CMD_STRING,\
		ft_strlen(COMMENT_CMD_STRING)))
			parse_nc(data, s, 1);
		else
			parse_label(data, s);
	}
}

// DELETE AFTER COMMENT

void		print_l(t_label *labels)
{
	t_label	*curr;

	curr = labels;
	ft_printf("\n");
	while (curr)
	{
		ft_printf("[%s]\t\t[%d]\n", curr->name, curr->line);
		curr = curr->next;
	}
	ft_printf("\n");

}

void		print_p(t_parts *parts)
{
	t_parts	*curr;

	curr = parts;
	while (curr)
	{
		ft_printf("[%d]\t[%d]\t[%d]\t\t\t[%s]\n", curr->token, curr->line, curr->value, curr->name);
		curr = curr->next;
	}
}

// DELETE BEFORE COMMENT

/*
**	@desc	- main parsing function
**	@param	- t_asm *data, main struct
*/

void		parse(t_asm *data)
{
	char	*s;

	while (get_line(data, data->rfd, &s, NULL))
	{
		if (s && ft_strlen(s) > 0)
			choose_parse(data, s);
		free(s);
	}
	free(s);
	if (!data->name || !data->comment)
		error(".name or .comment missing", 0);
	ft_printf("lines %d\n", data->lines);
	ft_printf(".name %s\t.comment %s\n", data->name, data->comment);
	print_l(data->labels);
	print_p(data->parts);
}
