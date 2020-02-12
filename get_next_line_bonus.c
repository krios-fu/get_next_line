/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 13:56:42 by krios-fu          #+#    #+#             */
/*   Updated: 2020/02/12 18:17:57 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_strdup(const char *s1)
{
	size_t		len;
	size_t		l;
	char		*snew;

	l = 0;
	len = ft_strlen((char *)s1) + 1;
	snew = (char *)malloc(len);
	if (snew == NULL)
		return (NULL);
	while (l < len)
	{
		snew[l] = s1[l];
		l++;
	}
	return ((char *)snew);
}

int				ft_nbytes(ssize_t *nbytes, char **getline)
{
	if (*nbytes < 0)
	{
		if (*getline != NULL)
		{
			free(*getline);
			*getline = NULL;
		}
		return (-1);
	}
	return (0);
}

int				ft_line_strdup(char **line)
{
	*line = ft_strdup("");
	return (0);
}

int				ft_gnl_n(ssize_t ret, char **getline, char **line)
{
	char		*tmp;
	char		*tmp2;

	if (ft_nbytes(&ret, getline))
		return (-1);
	if (!ret && !*getline)
		return (ft_line_strdup(line));
	if ((tmp = ft_strchr(*getline, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(*getline);
		tmp2 = ft_strdup(tmp + 1);
		free(*getline);
		*getline = tmp2;
		return (1);
	}
	if (ft_strchr(*getline, '\0'))
	{
		*line = ft_strdup(*getline);
		free(*getline);
		*getline = NULL;
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	ssize_t		ret;
	static char	*getline[4096];
	char		*buffer;

	ret = 0;
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 ||
		(!(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (!getline[fd])
			getline[fd] = ft_strdup(buffer);
		else
			getline[fd] = ft_strjoin(getline[fd], buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (ft_gnl_n(ret, &getline[fd], &*line));
}
