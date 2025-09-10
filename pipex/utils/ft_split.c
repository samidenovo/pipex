/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samalves <samalves@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:46:59 by samalves          #+#    #+#             */
/*   Updated: 2025/09/10 22:47:18 by samalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_countsub(const char *s, char c);
static int	ft_fillwords(char **result, const char *s, char c);
static char	*ft_nextword(const char *s, int *i, char c);
static void	ft_freemalloc(char **result, int k);

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc((ft_countsub(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!ft_fillwords(result, s, c))
		return (NULL);
	return (result);
}

static int	ft_countsub(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static int	ft_fillwords(char **result, const char *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			result[k] = ft_nextword(s, &i, c);
			if (!result[k])
				return (ft_freemalloc(result, k), 0);
			k++;
		}
	}
	result[k] = NULL;
	return (1);
}

static char	*ft_nextword(const char *s, int *i, char c)
{
	int	start;
	int	len;

	start = *i;
	len = 0;
	while (s[*i] && s[*i] != c)
	{
		(*i)++;
		len++;
	}
	return (ft_substr(s, start, len));
}

static void	ft_freemalloc(char **result, int k)
{
	while (--k >= 0)
		free(result[k]);
	free (result);
}
