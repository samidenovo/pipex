/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 22:18:33 by samalves          #+#    #+#             */
/*   Updated: 2025/09/22 17:30:49 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	close_pipes(t_data *data, int **fd)
{
	int	i;

	i = 0;
	while (i < data->n_cmd - 1)
	{
		if (i != data->index && i != data->index - 1)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
		i++;
	}
}

static void	file_err(t_data *data)
{
	ft_printf("pipex: open: %s\n", strerror(errno));
	free_exit(data);
}

void	first_child(t_data *data, int **fd)
{
	int	file;

	close_pipes(data, fd);
	file = open(data->file1, O_RDONLY);
	if (file == -1)
		file_err(data);
	if (dup2(file, STDIN_FILENO) < 0)
	{
		ft_printf("pipex: dup2: %s\n", strerror(errno));
		close (file);
		free_exit(data);
	}
	close (file);
	if (dup2(fd[data->index][1], STDOUT_FILENO) < 0)
	{
		ft_printf("pipex: dup2: %s\n", strerror(errno));
		free_exit(data);
	}
	close(fd[data->index][1]);
	close(fd[data->index][0]);
	if (data->path[data->index] == NULL)
		free_pipes(data, fd);
	execve(data->path[data->index], data->cmd[data->index], data->envp);
	ft_printf("pipex: %s: %s\n", data->path[data->index], strerror(errno));
	free_exit(data);
}

void	middle_child(t_data *data, int **fd)
{
	close_pipes(data, fd);
	if (dup2(fd[data->index - 1][0], STDIN_FILENO) < 0)
	{
		ft_printf("pipex: dup2: %s\n", strerror(errno));
		free_exit(data);
	}
	close (fd[data->index - 1][0]);
	close(fd[data->index - 1][1]);
	if (dup2(fd[data->index][1], STDOUT_FILENO) < 0)
	{
		ft_printf("pipex: dup2: %s\n", strerror(errno));
		free_exit(data);
	}
	close(fd[data->index][1]);
	close(fd[data->index][0]);
	if (data->path[data->index] == NULL)
		free_pipes(data, fd);
	execve(data->path[data->index], data->cmd[data->index], data->envp);
	ft_printf("pipex: %s: %s\n", data->path[data->index], strerror(errno));
	free_exit(data);
}

void	last_child(t_data *data, int **fd)
{
	int	file;

	close_pipes(data, fd);
	if (dup2(fd[data->index - 1][0], STDIN_FILENO) < 0)
	{
		ft_printf("pipex: dup2: %s\n", strerror(errno));
		free_exit(data);
	}
	close(fd[data->index - 1][0]);
	close(fd[data->index - 1][1]);
	file = open(data->file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file == -1)
		file_err(data);
	if (dup2(file, STDOUT_FILENO) < 0)
	{
		ft_printf("pipex: dup2: %s\n", strerror(errno));
		free_exit(data);
	}
	close(file);
	if (data->path[data->index] == NULL)
		free_pipes(data, fd);
	execve(data->path[data->index], data->cmd[data->index], data->envp);
	ft_printf("pipex: %s: %s\n", data->path[data->index], strerror(errno));
	free_exit(data);
}
