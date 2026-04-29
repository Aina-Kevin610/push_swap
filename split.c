/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:20:05 by rivandri          #+#    #+#             */
/*   Updated: 2026/03/25 10:22:52 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else
		{
			i++;
		}
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static char	*word_dup(char const *s, char c)
{
	int		i;
	int		len;
	char	*dup;

	len = word_len(s, c);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static	void	free_split(char **s, int word_alloc)
{
	int	i;

	i = 0;
	while (i < word_alloc)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < (count_words(s, c)))
	{
		while (s[j] != '\0' && s[j] == c)
			j++;
		res[i++] = word_dup(s + j, c);
		if (!res[i - 1])
		{
			free_split(res, (i - 1));
			return (NULL);
		}
		j = j + word_len(s + j, c);
	}
	res[i] = NULL;
	return (res);
}
