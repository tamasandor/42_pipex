/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:42:20 by atamas            #+#    #+#             */
/*   Updated: 2024/05/11 23:46:17 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (execve(pathcommand, command, envp) == -1)
	{
		write(2, "Command error\n", 14);
		free_multi(path);
		free_multi(command);
		exit(1);
	}
	return (0);
}

char	**parse_command(char *cmd)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	if (!command_is_correct(cmd))
	{
		write(2, "Command is not correct\n", 23);
		exit(1);
	}
	cmd = multi_quetes(cmd);
	res = ft_split(cmd, 26);
	if (!res || !res)
	{
		write(2, "Allocation failed or wrong command\n", 35);
		return (free_multi(res), NULL);
	}
	return (res);
}

void	parent(int dupable, int pipe0, int pipe1, char *command, char **envp, char **path)
{
		dup2(dupable, 0);
		close(pipe0);
		dup2(pipe1, 1);
		execute_command(path, parse_command(command), envp);
}

int	main(int argc, char *argv[], char **envp)
{
	int		first;
	char	**path;
	int		pid;
	int		fd[2];
	int		file2;

	if (argc != 5)
	{
		write(2, "Not enough arguments\n", 21);
		exit(1);
	}
	file2 = open_file(argv[argc - 1], 1);
	first = open_file(argv[1], 0);
	if (pipe(fd) == -1)
	{
		write(2, "Pipe failed\n", 12);
		exit (1);
	}
	path = extract_path(envp);
	pid = fork();
	if (pid == 0)
		parent(first, fd[0], fd[1], argv[2], envp, path);
	else if (pid == -1)
		forking_fail(path);
	else
	{
		waitpid(pid, NULL, 0);
		pid = fork();
		if (pid == 0)
			parent(fd[0], fd[1], file2, argv[3], envp, path);
		else if (pid == -1)
			forking_fail(path);
		else
		{
			close(fd[0]);
			close(fd[1]);
			close(first);
			waitpid(pid, NULL, 0);
			close(file2);
			free_multi(path);
		}
	}
}
