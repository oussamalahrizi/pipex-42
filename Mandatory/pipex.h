/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/12/01 20:15:12 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/01 20:15:12 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define INVALID_ARGS "Invalid arguments.\n"
# define ERR_FILES "Error with opening files."
# define ERR_PIPE "Error with pipe."
# define ERR_CMD "Command not found.\n"
# define ERR_FORK "Failed to fork."
# define ERR_PATH "path not found.\n"

typedef struct pip
{
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd;
	char	**cmd_args;
	int		fd[2];
	int		input;
	int		output;
	char	**paths;
}	t_tube;

char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
void	p_error(char *str);
void	error(char *str);
void	first_child(t_tube pipex, char **av);
void	second_child(t_tube *pipex, char **av);
char	*get_command(char **path, char *cmd);
char	*find_path(char **env);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif
