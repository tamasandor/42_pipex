/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 01:27:22 by atamas            #+#    #+#             */
/*   Updated: 2024/05/23 13:13:10 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

int		argument_correct(int argc, char **argv);
char	**extract_path(char *envp[]);
char	*multi_quetes(char *cmd);
int		open_file(char *file, int create);
char	*command_exists(char **path, char *command);
void	free_multi(char **mem);

typedef struct s_struct
{
	int		fd[2];
	int		readfile;
	int		writefile;
	char	**path;
	char	**envp;
}	t_struct;

#endif