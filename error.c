/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:42:20 by atamas            #+#    #+#             */
/*   Updated: 2024/05/06 19:27:51 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	return (NULL);
}

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
		printf("here: %s\n", command_plus_program);
		if (access(command_plus_program, X_OK) == 0)
		{
			printf("Found it %s\n", command_plus_program);
			return (free(command_with_slash), command_plus_program);
		}
		free(command_plus_program);
		i++;
	}
	return (free(command_with_slash), NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		first;
	char	*freeable;
	char	**path;

	if (argc != 5)
		write(2, "Not enough arguments\n", 22);
	/* 
	Check if the command is avalible on the local path
	otherwise pass it to the command_exist and then free it after use
	 */
	path = extract_path(envp);
	freeable = command_exists(path, argv[1]);
	printf("%s\n", freeable);
	free(freeable);
	print_multi(path, 1);
	/* first = open(argv[1], O_RDONLY);
	if (first == -1)
	{
		write(2, "Error opening the file\n", 24);
		exit(1);
	} */
}
