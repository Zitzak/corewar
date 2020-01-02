/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   args.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/02 21:34:48 by asulliva       #+#    #+#                */
/*   Updated: 2020/01/02 21:35:33 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/dsm.h"

/*
**	@desc	- function finds out what type of arguments are coming
**			- and fills them in accordingly
**	@param	- t_op *curr, the current op
**			- int enc_byte, the encoding byte, already shifted (enc_byte >> 2)
**			- use enc_byte to find out what argument types are coming up
**			- int arg_amnt, amount of arguments expected for this operation
**			- int op, the operation code
**	@return	- int size, amount of bytes read
*/

int			find_args(t_op *curr, int enc_byte, int arg_amnt, int op)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	curr->args = (char**)ft_memalloc(sizeof(char*) * arg_amnt + 1);
	while (i < arg_amnt)
	{
		//parse the encoding byte curr->args[i] would be
		//if 01 curr->args[i] = ft_strdup("r")
		//if 10 curr->args[i] = ft_strdup("%")
		//if 11 curr->args[i] = ft_strdup("")
		//somehow get argument value. size + amount of bytes
		//add , to arg if i < arg_amnt - 1
		i++;
	}
	enc_byte = 0;
	op = 0;
	return (size);
}