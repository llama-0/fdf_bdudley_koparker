/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koparker_get_next_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 22:57:29 by koparker          #+#    #+#             */
/*   Updated: 2019/09/23 20:02:35 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h> 

/*
** task-specific strjoin function.
** In the first call of the gnl-function holder is empty,
** so it's strduped with buf value. In other cases it joins
** existing holder and new buf.
*/

static char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*res;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(res = ft_strnew(len1 + len2 + 2)))
		return (NULL);
	while (i < (len1 + len2))
	{
		if (i < len1)
			res[i] = s1[i];
		else if (i - len1 < len2)
			res[i] = s2[i - len1];
		i++;
	}
	return (res);
}

static void	read_line(int fd, char **holder, char *buf)
{
	int		ret;
	char	*tmp;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = holder[fd];
		holder[fd] = ft_strjoin_gnl(tmp, buf);
		free(tmp);
		if (ft_strchr(holder[fd], '\n') != NULL)
			break ;
	}
}

static int	write_line(int fd, char **holder, char **line)
{
	char	*tmp;
	char	*tmp2;
	size_t	idx;

	if ((tmp = ft_strchr(holder[fd], '\n')) != NULL)
	{
		idx = tmp - holder[fd];
		*line = ft_strsub(holder[fd], 0, idx);
		tmp2 = holder[fd];
		holder[fd] = ft_strdup(&tmp2[idx] + 1);
		free(tmp2);
		return (1);
	}
	if (*holder[fd])
	{
		*line = ft_strdup(holder[fd]);
		free(holder[fd]);
		holder[fd] = NULL;
		return (1);
	}
	free(holder[fd]);
	holder[fd] = NULL;
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char		*holder[MAX_FDS];
	char			*buf;

	if (fd < 0 || read(fd, NULL, 0) < 0 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	if (!(buf = ft_memalloc(BUFF_SIZE + 1)))
		return (-1);
	read_line(fd, holder, buf);
	free(buf);
	if (holder[fd])
		return (write_line(fd, holder, line));
	return (0);
}

// static void	ft_delete(t_list **my_list, t_list **copy)
// {
// 	t_list *tmp;

// 	tmp = *my_list;
// 	if (*my_list == *copy)
// 	{
// 		*my_list = (*my_list)->next;
// 		free(tmp);
// 		tmp = NULL;
// 		return ;
// 	}
// 	while (tmp->next != *copy)
// 		tmp = tmp->next;
// 	tmp->next = (*copy)->next;
// 	free(*copy);
// 	*copy = NULL;
// }

// static int	get_line(char ***line, void **str, char c)
// {
// 	char *str_copy;

// 	str_copy = NULL;
// 	**line = (ft_strcmp((char *)(*str), "")) ?
// 	ft_strsub((char const *)(*str), 0,
// 	ft_strchr((const char*)(*str), c) - (char *)(*str)) : NULL;
// 	if (c == '\n')
// 		if (!(str_copy = ft_strdup(ft_strchr((const char *)(*str), c) + 1)))
// 			return (-1);
// 	ft_memdel(&(*str));
// 	*str = (void*)str_copy;
// 	if (**line != NULL)
// 		return (1);
// 	return (0);
// }

// static int	read_line(int fd, void **str, char ***line)
// {
// 	char	*str_copy;
// 	char	buf[BUFF_SIZE + 1];
// 	int		result;

// 	if (ft_strchr((const char*)(*str), '\n') != NULL)
// 		return (get_line(&(*line), &(*str), '\n'));
// 	while ((result = read(fd, buf, BUFF_SIZE)))
// 	{
// 		if (result == -1)
// 			return (-1);
// 		buf[result] = '\0';
// 		if (!(str_copy = ft_strjoin((char const *)(*str), (char const *)buf)))
// 			return (-1);
// 		free((*str));
// 		(*str) = (void *)str_copy;
// 		if (ft_strchr((const char*)(*str), '\n') != NULL)
// 			return (get_line(&(*line), &(*str), '\n'));
// 	}
// 	return (0);
// }

// int			get_next_line(const int fd, char **line)
// {
// 	static t_list	*my_list = NULL;
// 	t_list			*copy;
// 	int				result;
// 	char			buf[1];

// 	if (fd < 0 || line == NULL || (*line = NULL) || read(fd, &buf, 0) < 0)
// 		return (-1);
// 	copy = my_list;
// 	while (copy != NULL && copy->content_size != (size_t)fd)
// 		copy = copy->next;
// 	if (copy == NULL)
// 	{
// 		ft_lstadd(&my_list, ft_lstnew("", 1));
// 		my_list->content_size = fd;
// 		copy = my_list;
// 	}
// 	if ((result = read_line(fd, &copy->content, &line)))
// 		return (result);
// 	if (ft_strchr((const char*)copy->content, '\0') != NULL)
// 	{
// 		result = get_line(&line, &(copy->content), '\0');
// 		ft_delete(&my_list, &copy);
// 		return (result);
// 	}
// 	return (-1);
// }
