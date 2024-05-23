/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:28:28 by atamas            #+#    #+#             */
/*   Updated: 2024/05/23 10:37:11 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	argument_correct(int argc, char **argv)
{
	if (argc != 5)
	{
		write(2, "Correct use is ./pipex file1 cmd1 cmd2 file2\n", 45);
		return (0);
	}
	while (*argv)
	{
		if (!*argv || *argv[0] == ' ')
		{
			write(2, "Correct use is ./pipex file1 cmd1 cmd2 file2\n", 45);
			return (0);
		}
		argv++;
	}
	return (1);
}
