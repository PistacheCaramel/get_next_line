/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:24:09 by ybendavi          #+#    #+#             */
/*   Updated: 2021/03/24 13:30:05 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*saved(char *str, char *rst)
{
	int	i;

	i = 0;
	*str = 0;
	if (rst != NULL)
	{
		while (rst != NULL && rst[i])
		{
			str[i] = rst[i];
			i++;
		}
		str[i] = 0;
		free(rst);
	}
	return (str);
}

int		return_conditions(char *buffer, char *str, int res, char **line)
{
	char	*ptr;

	free(buffer);
	if (res == -1)
	{
		free(str);
		return (res);
	}
	ptr = str;
	if (ft_strchr(str, '\n') != NULL)
	{
		if (ft_strchr(str, '\n')[1] != 0)
			res = 1;
		ptr = str;
		ft_strchr(str, '\n')[0] = 0;
		str = ft_strdup(str);
		free(ptr);
	}
	(*line) = str;
	if (res == -1 || res == 0)
		return (res);
	else
		return (1);
}

int		freeer(char *buffer, char *str)
{
	free(buffer);
	free(str);
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	char		*str;
	char		*buffer;
	int			res;
	static char	*rst[1024];

	if (line == NULL || fd < 0)
		return (-1);
	res = 3;
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!(str = malloc(sizeof(char) * (ft_strlen(rst[fd]) + 1))))
		return (-1);
	str = saved(str, rst[fd]);
	rst[fd] = NULL;
	while (res != 0 && res != -1 && ft_strchr(str, '\n') == NULL)
	{
		if ((res = read(fd, buffer, BUFFER_SIZE)) == -1)
			return (freeer(buffer, str));
		buffer[res] = 0;
		str = ft_strjoin_free(str, buffer);
		ft_bzero(buffer, res + 1);
	}
	if (ft_strchr(str, '\n') != NULL)
		rst[fd] = ft_strdup(&ft_strchr(str, '\n')[1]);
	return (return_conditions(buffer, str, res, line));
}
