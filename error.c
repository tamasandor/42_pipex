/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:42:20 by atamas            #+#    #+#             */
/*   Updated: 2024/05/11 14:35:15 by atamas           ###   ########.fr       */
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

int	execute_command(char **path, char **command, char **envp)
{
	char	*pathcommand;

	pathcommand = command_exists(path, command[0]);
	if (!pathcommand)
	{
		write(2, "Program doesn't exist\n", 23);
		free_multi(path);
		free_multi(command);
		exit(1);
	}
	execve(pathcommand, command, envp);
}


int	main(int argc, char *argv[], char **envp)
{
	int		first;
	char	**command;
	char	**path;

	if (argc != 5)
		write(2, "Not enough arguments\n", 22);
	first = open(argv[1], O_RDONLY);
	if (first == -1)
	{
		write(2, "Error opening the file\n", 24);
		exit(1);
	}
	path = extract_path(envp);
	command = ft_split(argv[2], ' ');
	if (!command)
	{
		write(2, "Allocation failed\n", 19);
		free_multi(path);
		exit(1);
	}
	int	pid = fork();
	if (pid == 0)
		execute_command(path, command, envp);
	else
	{
		print_multi(path, 0, 1);
		free_multi(command);
	}
}
