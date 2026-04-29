/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:26:13 by airandri          #+#    #+#             */
/*   Updated: 2026/02/21 23:24:31 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_fill(int fd, char *stash, char *buffer)
{
	ssize_t	size;
	char	*ptr;

	if (!stash)
		stash = ft_strdup("");
	if (!stash || !buffer)
		return (NULL);
	size = 1;
	while (size > 0 && !ft_strchr(stash, '\n'))
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1)
		{
			free(stash);
			return (NULL);
		}
		buffer[size] = '\0';
		ptr = stash;
		stash = ft_strjoin(ptr, buffer);
		free(ptr);
	}
	return (stash);
}

char	*set_line(char *stash)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	ptr = (char *) malloc (sizeof (char) * (i + 2));
	if (!ptr)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		ptr[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		ptr[i] = '\n';
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*stash_update(char *stash)
{
	char	*temp;
	int		i;
	int		len;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	i++;
	len = ft_strlen (stash) - i;
	temp = ft_substr (stash, i, len);
	free (stash);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash = read_and_fill(fd, stash, buffer);
	free (buffer);
	if (!stash || *stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = set_line(stash);
	stash = stash_update(stash);
	if (stash && *stash == '\0')
	{
		free (stash);
		stash = NULL;
	}
	return (line);
}

int main(int argc, char *argv[])
{
  char *line = get_next_line(0);
  printf("van %s", line);
  return EXIT_SUCCESS;
}
