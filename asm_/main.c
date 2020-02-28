/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abumbier <abumbier@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 14:17:50 by asulliva       #+#    #+#                */
/*   Updated: 2020/02/28 16:08:56 by abumbier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

/*
**	@desc	- initialized the file to be opened
**	@param	- int ac, the number of arguments
**			- char **av, the arguments
**	@return	- t_asm *data, open file and malloced struct
*/

static t_asm	*init(int ac, char **av)
{
	t_asm	*data;

	data = (t_asm*)ft_memalloc(sizeof(t_asm));
	data->parts = NULL;
	data->labels = NULL;
	data->lines = 0;
	data->char_name = av[ac - 1];
	data->rfd = open(av[ac - 1], O_RDONLY);
	if (data->rfd < 3 || read(data->rfd, data->name, 0) < 0)
		return (NULL);
	return (data);
}

/*
**	@desc	- function checks if the file is a .s file
**	@param	- char *file, name of the file given as argument
*/

static void		check_file(char *file)
{
	int		len;

	len = ft_strlen(file);
	if (file[len - 1] == 's' && file[len - 2] == '.')
		return ;
	else
		error("File exstension must be .s", 0);
}

void			print_parts(t_parts *parts)
{
	t_parts	*curr;

	curr = parts;
	while (curr)
	{
		printf("__%s__\n", curr->name);
//		free(curr->name);
		curr = curr->next;
	}
}

/*
**	@desc	- main controller function
**	@param	- int ac, the number of arguments
**			- char **av, the arguments
**	@return	- 0
*/

int				main(int ac, char **av)
{
	t_asm	*data;

	if (ac < 2)
		error("usage ./asm <file_name>", 0);
	check_file(av[ac - 1]);
	data = init(ac, av);
	if (!data)
		error("Invalid file", 0);
	parse(data);
	close(data->rfd);
//	print_parts(data->parts);
	check_syntax(data);
	create_cor(data);
	close(data->wfd);
	free_data(data);
	return (0);
}
