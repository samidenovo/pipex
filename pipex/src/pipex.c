/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:58:41 by samalves          #+#    #+#             */
/*   Updated: 2025/09/10 23:08:04 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parent_process(t_data *data, int *fd)
{
	int	file;

	close(fd[1]);
	file = open(data->file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file == -1)
	{
		ft_printf("pipex: open: %s\n", strerror(errno));
		free_exit(data);
	}
	if (dup2(fd[0], STDIN_FILENO) < 0)
	{
		ft_printf("pipex: dup2: %s\n", strerror(errno));
		free_exit(data);
	}
	close(fd[0]);
	if (dup2(file, STDOUT_FILENO) < 0)
	{
		ft_printf("pipex: dup2: %s\n", strerror(errno));
		close(file);
		free_exit(data);
	}
	close(file);
	execve(data->path2, data->cmd2, data->envp);
	ft_printf("pipex: execve: %s: %s\n", data->path2, strerror(errno));
	free_exit(data);
}

static void	child_process(t_data *data, int	*fd)
{
	int	file;

	close(fd[0]);
	file = open(data->file1, O_RDONLY);
	if (file == -1)
	{
		ft_printf("pipex: open: %s\n", strerror(errno));
		free_exit(data);
	}
	if (dup2(file, STDIN_FILENO) < 0)
	{
		ft_printf("pipex: dup2: %s\n", strerror(errno));
		close(file);
		free_exit(data);
	}
	close(file);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
	{
		ft_printf("pipex: dup2: %s\n", strerror(errno));
		free_exit(data);
	}
	close(fd[1]);
	execve(data->path1, data->cmd1, data->envp);
	ft_printf("pipex: execve: %s: %s\n", data->path1, strerror(errno));
	free_exit(data);
}

void	pipex(t_data *data)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		ft_printf("pipex: pipe: %s\n", strerror(errno));
		free_exit(data);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_printf("pipex: %s\n", strerror(errno));
		free_exit(data);
	}
	else if (pid == 0)
		child_process(data, fd);
	else
		parent_process(data, fd);
}
