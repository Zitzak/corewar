/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: asulliva <asulliva@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 15:29:36 by asulliva       #+#    #+#                */
/*   Updated: 2020/02/06 17:11:35 by asulliva      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASM_H
# define __ASM_H
# define MAX_INT 2147483647
# define DIR_ARG1	(int[]) {LIVE,LD,AND,OR,XOR,ZJMP,LDI,FORK,LLD,LLDI,LFORK}
# define DIR_ARG2	(int[]) {AND,OR,XOR,LDI,STI,LLDI}
# define DIR_ARG3	(int[]) {STI}
# define IND_ARG1	(int[]) {LD,AND,OR,XOR,LDI,LLD,LLDI}
# define IND_ARG2	(int[]) {ST,AND,OR,XOR,STI}
# define REG_ARG1	(int[]) {ST,ADD,SUB,OR,XOR,LDI,STI,LLDI,AFF}
# define REG_ARG2	(int[]) {LD,ST,ADD,SUB,AND,OR,XOR,LDI,STI,LLD,LLDI}
# define REG_ARG3	(int[]) {ADD,SUB,AND,OR,XOR,LDI,STI,LLDI}

# define DIR -1
# define REG -2
# define IND -3
# define LIVE 0x01
# define LD 0x02
# define ST 0x03
# define ADD 0x04
# define SUB 0x05
# define AND 0x06
# define OR 0x07
# define XOR 0x08
# define LLD 0x0d
# define AFF 0x10
# define ZJMP 0x09
# define LDI 0x0a
# define STI 0x0b
# define FORK 0x0c
# define LLDI 0x0e
# define LFORK 0x0f

# include <fcntl.h>
# include <unistd.h>
# include "../../ft_printf/includes/ft_printf.h"
# include "../../VM/includes/op.h"

typedef struct s_asm	t_asm;
typedef struct s_label	t_label;
typedef struct s_parts	t_parts;

struct					s_parts {
	char				*name;
	int					token;
	int					line;
	int					value;
	int					size;
	int					line_size;
	t_parts				*next;
};

struct					s_label {
	char				*name;
	int					line;
	t_label				*next;
};

struct					s_asm {
	int					rfd;
	int					wfd;
	int					lines;
	char				*name;
	char				*comment;
	char				*char_name;
	t_label				*labels;
	t_parts				*parts;	
};
/*
*************************************PARSE*************************************
*/
void					parse(t_asm *data);
int						get_line(t_asm *data, int fd, char **s, char **split);
void					parse_nc(t_asm *data, char *s, int type);
void					parse_label(t_asm *data, char *s);
void					get_label(t_asm *data, char **line);
void					parse_instruction(t_asm *data, char **line);
/*
*************************************UTILS*************************************
*/
void					error(char *message, int line);
int						check_instruction(char *s);
void					add_label(t_asm *data, t_label **new);
t_label					*make_label(t_asm *data, char *s, int line);
int						get_token(char *s);
int						get_value(int token, int line, char *s);
char					*rm_comma(char *s, int line);

/*
**************************************FREE*************************************
*/
void					free_arr(char **arr1, char ***arr2, int flag);
#endif