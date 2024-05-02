/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:30:20 by atamas            #+#    #+#             */
/*   Updated: 2024/05/02 19:14:02 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	int	firstfile;
	int	secondfile;

	if (argc < 5)
	{
		write(2, "Not enough arguments\n", 22);
		exit(1);
	}
	firstfile = open(argv[1], O_RDONLY);
	secondfile = open(argv[4], O_WRONLY | O_CREAT, 0666);
	if (firstfile == -1 || secondfile == -1)
	{
		write(2, "Error opening the file\n", 24);
		exit(1);
	}
}
