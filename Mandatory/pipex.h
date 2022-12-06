/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:15:12 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/01 20:15:12 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

#define INVALID_ARGS "Invalid arguments.\n"
#define ERR_INPUT "Error with input file"
#define ERR_OUTPUT "Error with output file"
#define ERR_PIPE "Error with pipe"
#define ERR_CMD "Error with command"

typedef struct pip
{
	pid_t	pid1;
	pid_t	pid2;
	char *cmd;
	char **cmd_args;
	int	fd[2];
	int	input;
	int	output;
	char **paths;
}	tube;

char	**ft_split(char *s, char c);
int	ft_strncmp(char*s1, char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
void p_error(char *str);
void	error(char *str);
void free_main(tube pipex);
void free_childs(tube pipex);
void first_child(tube pipex, char **av);
void second_child(tube pipex, char **av);
char *get_command(char **path, char *cmd);\
char *find_path(char **env);




#endif