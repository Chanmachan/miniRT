/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hommayunosuke <hommayunosuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 03:09:09 by hommayunosu       #+#    #+#             */
/*   Updated: 2022/07/12 03:09:10 by hommayunosu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char	*gnl_strchr(char *s, int c)
{
	char	*new_s;
	size_t	i;

	new_s = (char *) s;
	i = 0;
	if (!s)
		return (NULL);
	while (new_s[i] != '\0')
	{
		if (new_s[i] == (char) c)
			return (new_s + i);
		i++;
	}
	if ((char) c == '\0')
		return (new_s + i);
	return (NULL);
}

static char	*read_lines(char *str, int fd)
{
	char		*buf;
	ssize_t		rd_bytes;

	rd_bytes = 1;
	buf = (char *) malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (rd_bytes != 0 && !gnl_strchr(str, '\n'))
	{
		rd_bytes = read(fd, buf, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_bytes] = '\0';
		str = gnl_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

static char	*get_one_line(char *str)
{
	size_t	i;
	char	*rtn_str;

	if (str[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	rtn_str = gnl_substr(str, 0, i);
	if (rtn_str == NULL)
		return (NULL);
	return (rtn_str);
}

//str[0] == '\0' if empty

static char	*delete_last_line(char *str)
{
	size_t	i;
	char	*new_str;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	if (str[i] == '\n')
		i++;
	new_str = gnl_substr(&str[i], 0, gnl_strlen(&str[i]));
	if (new_str == NULL)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*rtn_str;
	char		*tmp;

	if ((size_t)BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	tmp = str;
	str = read_lines(str, fd);
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	rtn_str = get_one_line(str);
	str = delete_last_line(str);
	return (rtn_str);
}

/*#include <fcntl.h>//open
#include <stdio.h>

int main(void)
{
	char 	*str;
	int 	fd;
	size_t 	i;

	i = 0;
	fd = open("test/test.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
//		printf("[%zu] : %s\n-------------\n", i, str);
		printf("%s", str);
		if (str == NULL)
		{
			free(str);
			break;
		}
		free(str);
		i++;
	}
	close(fd);
	system("leaks -q a.out");
	return (0);
}*/
//-fsanitize=address -g