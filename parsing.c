/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:00:04 by atamas            #+#    #+#             */
/*   Updated: 2024/05/11 23:01:50 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*command_exists(char **path, char *command)
{
	char	*command_plus_program;
	char	*command_with_slash;
	int		i;

	i = 0;
	command = ft_strdup(command);
	if (access(command, X_OK) == 0)
		return (command);
	command_with_slash = ft_strjoin("/", command);
	free(command);
	while (path[i])
	{
		command_plus_program = ft_strjoin(path[i], command_with_slash);
		if (access(command_plus_program, X_OK) == 0)
			return (free(command_with_slash), command_plus_program);
		free(command_plus_program);
		i++;
	}
	write(2, "Command doesn't exist\n", 22);
	return (free(command_with_slash), NULL);
}

char	**extract_path(char *envp[])
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strchr(envp[i], '/');
			break ;
		}
		i++;
	}
	if (path != NULL)
		return (ft_split(path, ':'));
	write(2, "Path not found\n", 16);
	exit(1);
}

char	*multi_quetes(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			j = i + 1;
			while (cmd[j] && cmd[i] != cmd[j])
				j++;
			if (cmd[j])
			{
				cmd[i] = 26;
				cmd[j] = 26;
				i = j;
			}
		}
		else if (cmd[i] == ' ')
			cmd[i] = 26;
		i++;
	}
	return (cmd);
}
