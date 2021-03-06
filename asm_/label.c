/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   label.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abumbier <abumbier@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 14:31:21 by asulliva       #+#    #+#                */
/*   Updated: 2020/02/28 19:30:37 by abumbier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

/*
**	@desc	- function checks if the label contains only the allowed characters
**	@param	- char *label, name of the label to be checked
**	@return	- int, 0 if not valid
**			- 1 if valid
*/

int			check_label(char *label)
{
	int		i;

	i = 0;
	while (label[i] != '\0')
	{
		if (!ft_strchr(LABEL_CHARS, label[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
**	@desc	- adds a label to the linked list of labels
**	@param	- t_asm *data, main struct
**			- t_label *new, label to be added
*/

void		add_label(t_asm *data, t_label **new)
{
	t_label	*curr;

	curr = data->labels;
	if (!curr)
	{
		data->labels = (*new);
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = (*new);
}

static void	label_syntax(char *label, int line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (label[i])
	{
		if (label[i] == LABEL_CHAR)
			count++;
		i++;
	}
	if (count > 1)
		error("Invalid label syntax", line);
}

/*
**	@desc	- function gets the label and all the variables
**	@param	- t_asm *data, main struct
**			- char **line, line read, split on whitespace
*/

void		get_label(t_asm *data, char **line)
{
	t_label		*new;
	char		**split;
	int			line_nb;

	split = NULL;
	label_syntax(line[0], data->lines);
	split = ft_strsplit(line[0], LABEL_CHAR);
	if (split[1])
	{
		new = make_label(data, split[0], data->lines);
		add_label(data, &new);
		ft_strclr(line[0]);
		line[0] = ft_strdup(split[1]);
		parse_instruction(data, line);
	}
	else if (line[1] && check_instruction(line[1]))
	{
		line_nb = data->lines;
		parse_instruction(data, &line[1]);
		new = make_label(data, split[0], line_nb);
		add_label(data, &new);
	}
	else
		get_next_label(data, split[0]);
	free_arr(NULL, &split, 1);
}

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
