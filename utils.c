/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:34:24 by atamas            #+#    #+#             */
/*   Updated: 2024/05/23 11:59:45 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
