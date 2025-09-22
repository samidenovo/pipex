/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:51:23 by samalves          #+#    #+#             */
/*   Updated: 2025/09/22 00:30:19 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	pipe_err(t_data *data, int **fd, int i, char *msg)
{
	ft_printf("pipex: %s: %s\n", msg, strerror(errno));
	while (i >= 0)
	{
		free(fd[i]);
		i--;
	}
	free(fd);
	free_exit(data);
}

static int	**allocate_pipes(t_data *data)
{
	int	**fd;
	int	i;

	i = 0;
	fd = malloc((data->n_cmd - 1) * sizeof(int *));
	if (!fd)
		pipe_err(data, fd, i, "allocation");
	while (i < data->n_cmd - 1)
	{
		fd[i] = malloc(2 * sizeof(int));
		if (!fd[i])
			pipe_err(data, fd, i, "allocation");
		if (pipe(fd[i]) == -1)
			pipe_err(data, fd, i, "pipe");
		i++;
	}
	return (fd);
}

static void	fork_process(t_data *data, int **fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_printf("pipex: %s\n", strerror(errno));
		free_exit(data);
	}
	else if (pid == 0)
	{
		if (data->index == 0)
			first_child(data, fd);
		else if (data->index == data->n_cmd - 1)
			last_child(data, fd);
		else
			middle_child(data, fd);
	}
	data->index++;
}

void	pipex(t_data *data)
{
	int		**fd;
	int		i;
	int		status;

	fd = allocate_pipes(data);
	while (data->index < data->n_cmd)
		fork_process(data, fd);
	i = 0;
	while (i < data->n_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
		i++;
	}
	free(fd);
	while (waitpid(-1, &status, 0) > 0)
		;
}
