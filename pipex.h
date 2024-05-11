/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 01:27:22 by atamas            #+#    #+#             */
/*   Updated: 2024/05/11 23:04:01 by atamas           ###   ########.fr       */
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

// test
# include <stdio.h>

void	print_multi(char **mem, int print, int f);
void	free_multi(char **mem);
int		open_file(char *file, int create);
int		command_is_correct(char *cmd);
char	*command_exists(char **path, char *command);
char	**extract_path(char *envp[]);
char	*multi_quetes(char *cmd);
void	forking_fail(char **cmd, char **path);

#endif