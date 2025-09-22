/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:28:49 by samalves          #+#    #+#             */
/*   Updated: 2025/09/22 00:15:30 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_data	*init_struct(char **av, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_printf("pipex: allocation: %s\n", strerror(errno));
		exit (1);
	}
	data->file1 = av[1];
	data->file2 = av[4];
	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	data->path1 = NULL;
	data->path2 = NULL;
	data->envp = envp;
	return (data);
}

static void	check_files(t_data *data)
{
	if (access(data->file1, R_OK) == -1)
	{
		ft_printf("pipex: %s: %s\n", data->file1, strerror(errno));
		free_exit(data);
	}
	if (access(".", W_OK) == -1)
	{
		ft_printf("pipex: %s: %s\n", data->file2, strerror(errno));
		free_exit(data);
	}
}

static char	*find_cmd_path(char *cmd, char *envp)
{
	char	*path;
	char	*temp;
	char	**arrpath;
	int		i;

	arrpath = ft_split(envp, ':');
	i = 0;
	while (arrpath[i] != NULL)
	{
		temp = ft_strjoin(arrpath[i], "/");
		path = ft_strjoin(temp, cmd);
		if (access(path, X_OK) == 0)
		{
			free (temp);
			free_array(arrpath);
			return (path);
		}
		free (temp);
		free (path);
		i++;
	}
	free_array(arrpath);
	return (NULL);
}

static void	parse_data(t_data *data)
{
	int	i;
	int	j;

	check_files(data);
	i = 0;
	j = -1;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
			j = i;
		i++;
	}
	if (j == -1)
	{
		ft_printf("pipex: PATH not found\n");
		free_exit(data);
	}
	data->path1 = find_cmd_path(data->cmd1[0], data->envp[j] + 5);
	data->path2 = find_cmd_path(data->cmd2[0], data->envp[j] + 5);
	if (data->path1 == NULL)
		ft_printf("pipex: %s: command not found\n", data->cmd1[0]);
	if (data->path2 == NULL)
		ft_printf("pipex: %s: command not found\n", data->cmd2[0]);
	if (data->path2 == NULL)
		free_exit(data);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	if (ac != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (2);
	}
	data = init_struct(av, envp);
	parse_data(data);
	pipex(data);
	return (0);
}
