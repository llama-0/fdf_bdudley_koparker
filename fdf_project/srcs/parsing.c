/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:11:59 by koparker          #+#    #+#             */
/*   Updated: 2019/09/10 13:35:23 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		parse_line(char ***split, int **data)
{
	int		j;

	j = 0;
	while (split[0][j])
	{
		if (valid_nbr(split[0][j], &(*data)[j]) == 0)
			return (0);
		if (valid_color(split[0][j], &(*color)[j] == 0)
			return (0);
		j++;
	}
	return (1);
}

void	free_struct(t_data **map, int i)
{
	int	j;

	j = 0;
	if ((*map)->data && (*map)->data[j])
	{
		while (j < i)
		{
			free((*map)->data[j]);
			(*map)->data[j] = NULL;
			j++;
		}
	}
	if ((*map)->data)
	{
		free((*map)->data);
		(*map)->data = NULL;
	}
	free(*map);
	*map = NULL;
	exit(0);
}

t_data	*read_data2(const int fd)
{
	char	**split;

	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
	}
}

t_data	*read_data(const int fd)
{
	int		i;
	t_data	*map;
	char	*line;
	char	**split;

	i = 0;
	if ((map = (t_data *)malloc(sizeof(t_data))) == NULL)
		exit(0);
	map->data = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		map->len = ft_2d_strlen(split);
		if (i == 0)
			map->length = map->len;
		if (map->len != map->length)
			free_struct(&map, i);
		if (map->data == NULL)
		{
			if ((map->data = (int **)malloc(sizeof(int *) * map->len)) == NULL)
				free_struct(&map, i);
		}
		if ((map->data[i] = (int *)malloc(sizeof(int) * map->len)) == NULL)
			free_struct(&map, i);
		ft_memset(map->data[i], 0, map->len);
		if (parse_line(&split, &(map->data[i])) == 0)
			free_struct(&map, i);
		i++;
	}
	map->height = i;
	return (map);
}
