/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:01:19 by atamas            #+#    #+#             */
/*   Updated: 2024/05/27 19:22:51 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	read_process(char *argv, t_struct *data)
{
	char	**cmd;
	char	*rootcmd;

	argv = multi_quetes(argv);
	cmd = ft_split(argv, 26);
	rootcmd = command_exists(data->path, cmd[0]);
	if (!rootcmd)
	{
		free_multi(data->path);
		free_multi(cmd);
		exit(127);
	}
	dup2(data->readfile, 0);
	dup2(data->fd[1], 1);
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->readfile);
	execve(rootcmd, cmd, data->envp);
	perror(rootcmd);
	free_multi(data->path);
	free_multi(cmd);
	exit(1);
}

static int	write_process(char *argv, t_struct *data)
{
	char	**cmd;
	char	*rootcmd;

	argv = multi_quetes(argv);
	cmd = ft_split(argv, 26);
	rootcmd = command_exists(data->path, cmd[0]);
	if (!rootcmd)
	{
		free_multi(data->path);
		free_multi(cmd);
		exit(127);
	}
	dup2(data->writefile, 1);
	dup2(data->fd[0], 0);
	close(data->fd[1]);
	close(data->fd[0]);
	close(data->writefile);
	execve(rootcmd, cmd, data->envp);
	perror(rootcmd);
	free_multi(data->path);
	free_multi(cmd);
	exit(1);
}

static void	multi_processes(char **argv, t_struct *data)
{
	int	pid;
	int	pid2;
	int	status;

	pid = fork();
	if (pid <= 0 && !fork_error(pid, data))
		read_process(argv[2], data);
	else
	{
		close(data->fd[1]);
		close(data->readfile);
		pid2 = fork();
		if (pid2 <= 0 && !fork_error(pid2, data))
			write_process(argv[3], data);
		else
		{
			waitpid(pid, NULL, 0);
			waitpid(pid2, &status, 0);
			close(data->fd[0]);
			close(data->writefile);
			free_multi(data->path);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				exit(WEXITSTATUS(status));
		}
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_struct	data;

	if (!argument_correct(argc, argv))
		exit(1);
	data.writefile = open_file(argv[argc - 1], 1);
	data.readfile = open_file(argv[1], 0);
	data.envp = envp;
	if (pipe(data.fd) == -1)
	{
		perror("pipe");
		close(data.writefile);
		close(data.readfile);
		exit(1);
	}
	data.path = extract_path(envp);
	multi_processes(argv, &data);
}
