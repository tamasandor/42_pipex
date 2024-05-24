/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:30:16 by atamas            #+#    #+#             */
/*   Updated: 2024/05/23 12:38:21 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**extract_path(char *envp[])
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] && !path)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = ft_strchr(envp[i], '/');
		i++;
	}
	if (path != NULL)
		return (ft_split(path, ':'));
	write(2, "Path not found\n", 16);
	exit(127);
}

char	*command_exists(char **path, char *command)
{
	char	*command_with_path;
	char	*command_with_slash;
	int		i;

	i = 0;
	if (ft_strlen(command) > 2 && command[0] == '.' && command[1] == '/')
	{
		if (access(command, X_OK) == 0)
			return (command);
		else
			return (NULL);
	}
	command_with_slash = ft_strjoin("/", command);
	while (path[i])
	{
		command_with_path = ft_strjoin(path[i], command_with_slash);
		if (access(command_with_path, X_OK) == 0)
			return (free(command_with_slash), command_with_path);
		free(command_with_path);
		i++;
	}
	write(2, "Command doesn't exist\n", 22);
	return (free(command_with_slash), NULL);
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
