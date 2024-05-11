/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:42:20 by atamas            #+#    #+#             */
/*   Updated: 2024/05/11 22:57:31 by atamas           ###   ########.fr       */
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
		return (-1);
	}
	return (0);
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

int	command_is_correct(char *cmd)
{
	if (!cmd || !cmd[0] || cmd[0] == ' ')
		return (0);
	return (1);
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

int	open_file(char *file, int create)
{
	int	fd;

	if (!file || !*file)
	{
		write(2, "Incorrect file name\n", 20);
		exit(1);
	}
	if (create)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Opening the file failed\n", 24);
		exit(1);
	}
	return (fd);
}

int	main(int argc, char *argv[], char **envp)
{
	int		first;
	char	**command;
	char	**path;
	int	pid;
	int		fd[2];
	int		file2;

	command = NULL;
	if (argc != 5)
	{
		write(2, "Not enough arguments\n", 21);
		exit(1);
	}
	file2 = open_file(argv[argc - 1], 1);
	first = open_file(argv[1], 0);
	path = extract_path(envp);
	command = parse_command(argv[2]);
	if (command == NULL)
	{
		free_multi(path);
		free_multi(command);
		exit(1);
	}
	if (pipe(fd) == -1)
	{
		write(2, "Pipe failed\n", 12);
		free_multi(path);
		free_multi(command);
		exit (1);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(first, 0);
		close(fd[0]);
		dup2(fd[1], 1);
		if (execute_command(path, command, envp) == -1)
		{
			write(2, "Error\n", 6);
			free_multi(path);
			exit(1);
		}
	}
	else if (pid == -1)
	{
		write(2, "Forkin failed\n", 14);
		free_multi(path);
		free_multi(command);
		exit(1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		pid = fork();
		if (pid == 0)
		{
			free_multi(command);
			command = parse_command(argv[3]);
			dup2(fd[0], 0);
			close(fd[1]);
			dup2(file2, 1);
			if (execute_command(path, command, envp) == -1)
				exit(1);
		}
		else if (pid == -1)
		{
			write(2, "Forkin failed\n", 14);
			free_multi(path);
			free_multi(command);
			exit(1);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			close(first);
			waitpid(pid, NULL, 0);
			close(file2);
			print_multi(path, 0, 1);
			free_multi(command);
		}
	}
}
