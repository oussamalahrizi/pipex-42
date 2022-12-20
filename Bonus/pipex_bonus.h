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

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	pid_t	pid;
	char	*cmd;
	char	**cmd_args;
	int		fd[2];
	int		infile;
	int		outfile;
	char	**paths;
	int		cmd_count;
}	t_pipe;

# define INVALID_ARGS "Invalid arguments.\n"
# define INVALID_ARGS_HERE_DOC "Invalid arguments for here_doc\n"
# define ERR_FILES "Error with opening files."
# define ERR_TEMP "Failed to create a temp file."
# define ERR_PIPE "Error with pipe."
# define ERR_CMD "Command not found.\n"
# define ERR_FORK "Failed to fork."
# define ERR_LINE "Failed to get the line."

char	**ft_split(char *s, char c);
int		ft_strncmp(char*s1, char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
void	p_error(char *str);
void	error(char *str);
char	*get_command(char **path, char *cmd);
char	*find_path(char **env);
void	free_child(t_pipe *pipex);
void	free_parent(t_pipe *pipex);
void	here_doc(int ac, char **av, char **env);
void	multi_pipes(int ac, char **av, char **env);
char	*find_path(char **env);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif
