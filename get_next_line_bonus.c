/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame <ommohame@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:24:27 by ommohame          #+#    #+#             */
/*   Updated: 2022/03/12 14:54:35 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*realloc_str(char *str, char *line)
{
	size_t		i;
	size_t		j;
	char		*tmp;

	i = 0;
	while (str[i] && str[i] == line[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = 0;
	free (str);
	return (tmp);
}

char	*linooo(char *str)
{
	size_t		i;
	char		*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\n')
		line[i] = str[i];
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*reading(char *str, char *bfr, int fd)
{
	int		ret;

	ret = read(fd, bfr, BUFFER_SIZE);
	if (ret == -1)
	{
		free (bfr);
		return (NULL);
	}
	bfr[ret] = 0;
	str = ft_strjoin(str, bfr);
	while (ret != 0 && !ft_strchr(str, '\n'))
	{
		ret = read(fd, bfr, BUFFER_SIZE);
		if (ret == -1)
		{
			free (bfr);
			return (NULL);
		}
		bfr[ret] = 0;
		str = ft_strjoin(str, bfr);
	}
	free(bfr);
	return (str);
}

char	*get_next_line(int fd)
{
	char			*bfr;
	static char		*str[1024];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bfr = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!bfr)
		return (NULL);
	str[fd] = reading(str[fd], bfr, fd);
	if (!str[fd])
		return (NULL);
	line = linooo(str[fd]);
	str[fd] = realloc_str(str[fd], line);
	return (line);
}
