/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:42:20 by atamas            #+#    #+#             */
/*   Updated: 2024/05/06 01:50:25 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"

// test
#include <stdio.h>

char	*extract_path(char *envp[])
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strchr(envp[i], '/');
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	int			first;
	const char	*path = extract_path(envp);
	/* first = open(argv[1], O_RDONLY);
	if (first == -1)
	{
		write(2, "Error opening the file\n", 24);
		exit(1);
	} */
}
