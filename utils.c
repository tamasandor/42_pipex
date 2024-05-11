/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:40:53 by atamas            #+#    #+#             */
/*   Updated: 2024/05/11 17:35:40 by atamas           ###   ########.fr       */
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
