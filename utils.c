/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:40:53 by atamas            #+#    #+#             */
/*   Updated: 2024/05/16 20:12:41 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_multi(char **mem, int print, int f)
{
	int	i;

	if (print)
	{
		i = 0;
		while (mem[i])
		{
			printf("%s\n", mem[i]);
			i++;
		}
	}
	if (f == 1)
		free_multi(mem);
}

void	free_multi(char **mem)
{
	int	i;

	if (mem)
	{
		i = 0;
		while (mem[i])
		{
			free(mem[i]);
			i++;
		}
		free(mem);
	}
}

int	open_file(char *file, int create)
{
	int	fd;

	fd = -1;
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
		write(2, "Error\n", 6);
		exit(1);
	}
	return (fd);
}

int	command_is_correct(char *cmd)
{
	if (!cmd || !cmd[0] || cmd[0] == ' ')
		return (0);
	return (1);
}

void	forking_fail(char **path)
{
	write(2, "Forking failed\n", 15);
	free_multi(path);
	exit(1);
}
