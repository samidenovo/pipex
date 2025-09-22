/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:06:27 by samalves          #+#    #+#             */
/*   Updated: 2025/09/22 01:54:43 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	***parsing_cmd(int ac, char **av, t_data *data)
{
	int		i;
	int		j;
	char	***arr;

	i = 2;
	j = 0;
	arr = malloc((ac - 3) * sizeof(char **));
	if (!arr)
	{
		ft_printf("pipex: allocation: %s\n", strerror(errno));
		free_exit(data);
	}
	while (i < ac - 1)
	{
		arr[j] = ft_split(av[i], ' ');
		i++;
		j++;
	}
	return (arr);
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
		free (temp);
		if (access(path, X_OK) == 0)
		{
			free_array(arrpath, -1);
			return (path);
		}
		free (path);
		i++;
	}
	free_array(arrpath, -1);
	return (NULL);
}

static int	index_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	ft_printf("pipex: PATH not found\n");
	free_exit(data);
	return (-1);
}

static char	**parsing_path(t_data *data)
{
	int		i;
	int		j;
	char	**path;

	j = index_path(data);
	path = malloc((data->n_cmd + 1) * sizeof(char *));
	if (!path)
	{
		ft_printf("pipex: allocation: %s\n", strerror(errno));
		free_exit(data);
	}
	i = 0;
	while (i < data->n_cmd)
	{
		path[i] = find_cmd_path(data->cmd[i][0], data->envp[j] + 5);
		if (path[i] == NULL)
			ft_printf("pipex: %s: command not found\n", data->cmd[i][0]);
		i++;
	}
	path[i] = NULL;
	return (path);
}

t_data	*init_struct(int ac, char **av, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_printf("pipex: allocation: %s\n", strerror(errno));
		exit (1);
	}
	data->file1 = av[1];
	data->file2 = av[ac - 1];
	data->envp = envp;
	data->n_cmd = ac - 3;
	data->cmd = parsing_cmd(ac, av, data);
	data->path = parsing_path(data);
	data->index = 0;
	return (data);
}
