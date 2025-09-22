/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:06:58 by samalves          #+#    #+#             */
/*   Updated: 2025/09/22 17:32:57 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_array(char **array, int size)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	if (size == -1)
	{
		while (array[i] != NULL)
		{
			free (array[i]);
			i++;
		}
	}
	else
	{
		while (i < size)
		{
			free (array[i]);
			i++;
		}
	}
	free (array);
}

void	free_triple(char ***array, int n_cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < n_cmd)
	{
		j = 0;
		while (array[i][j])
			j++;
		free_array(array[i], j);
		i++;
	}
	free (array);
}

void	free_exit(t_data *data)
{
	if (data->path)
		free_array(data->path, data->n_cmd);
	if (data->cmd)
		free_triple(data->cmd, data->n_cmd);
	free (data);
	exit (1);
}

void	free_pipes(t_data *data, int **fd)
{
	int	i;

	i = 0;
	while (i < data->n_cmd - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	free_exit(data);
}
