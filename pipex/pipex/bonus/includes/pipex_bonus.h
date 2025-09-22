/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:33:18 by samalves          #+#    #+#             */
/*   Updated: 2025/09/22 17:31:30 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libftprintf.h"
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data
{
	char	*file1;
	char	*file2;
	char	***cmd;
	char	**path;
	char	**envp;
	int		n_cmd;
	int		index;
}	t_data;

void	free_array(char **array, int index);
void	free_triple(char ***array, int n_cmd);
void	free_exit(t_data *data);
void	free_pipes(t_data *data, int **fd);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
t_data	*init_struct(int ac, char **av, char **envp);
void	pipex(t_data *data);
void	first_child(t_data *data, int **fd);
void	middle_child(t_data *data, int **fd);
void	last_child(t_data *data, int **fd);
int		main(int ac, char **av, char **envp);

#endif
