/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cursor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/05 17:28:27 by krioliin       #+#    #+#                */
/*   Updated: 2020/01/07 19:30:38 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/vm_arena.h"

bool	check_opcode(uint8_t opcode)
{
	return (1 <= opcode && opcode <= OP_NBR);
}

bool	check_encodbyte(uint8_t	opcode, uint8_t encoding_byte)
{
	e_argctype	argc_type[3];
	static bool	(*op_encode[17])(e_argctype *);

	if (!*op_encode[2])
		init_op_encode_validation_arr(op_encode);
	if (is_encoding_byte(opcode))
	{
		decode_encoding_byte(encoding_byte, argc_type);
		if (!(*op_encode[opcode])(argc_type))
			return (false);
	}
	return (true);
}

bool	check_reg(uint8_t opcode, uint8_t encoding_byte, uint8_t *arena)
{
	e_argctype	argc_type[3];
	short		i;
	short		j;

	i = 0;
	j = 0;
	if (is_encoding_byte(opcode))
	{
		decode_encoding_byte(encoding_byte, argc_type);
		while (i < 3)
		{
			if (argc_type[i] == REG && !(1 <= arena[j] && arena[j] <= OP_NBR))
				return (false);
			if (argc_type[i] == REG)
				j++;
			else if (argc_type[i] == IND)
				j += 2;
			else if (argc_type[i] == DIR)
				j += get_dir_size(opcode);			
			i++;
		}
	}
	return (true);
}

short	execute_cursor(t_cursor *cursor, uint8_t arena[MEM_SIZE], t_vm *vm)
{
	if (cursor->wait_cycles == 0)
	{
		if (!check_opcode(cursor->opcode))
		{
			cursor->pos += 1;
			return (0);
		}
		else if (
		check_encodbyte(cursor->opcode, arena[cursor->pos + 1]) &&
		check_reg(cursor->opcode, arena[cursor->pos + 1], &arena[cursor->pos + 2]))
		execute_operation(cursor, vm);
		if (cursor->opcode != ZJMP)
		{
			cursor->pos += cursor->pc;
			cursor->opcode = arena[cursor->pos];
			cursor->pc =
			calculate_program_counter(cursor->opcode, arena[cursor->pos + 1]);
		}
		// cursor->wait_cycles = get_waite_cycle();
	}
	else
		cursor->wait_cycles -= 1;
	return (0);
}
