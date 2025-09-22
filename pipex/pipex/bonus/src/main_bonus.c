/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:39:31 by samalves          #+#    #+#             */
/*   Updated: 2025/09/22 01:06:22 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	if (ac < 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
		return (2);
	}
	data = init_struct(ac, av, envp);
	check_files(data);
	pipex(data);
	free_array(data->path, data->n_cmd);
	free_triple(data->cmd, data->n_cmd);
	free (data);
	return (0);
}
