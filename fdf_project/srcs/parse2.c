/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:47:52 by koparker          #+#    #+#             */
/*   Updated: 2019/09/10 17:46:36 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_point		**new_array(t_point		***prev_array, t_data	*data)
{
	t_point **array;
	size_t	j;
	size_t	i;

	j = 0;
	array = (t_point **)malloc(sizeof(t_point *) * data->capacity_y);
	while (j < data->size_y)
	{
		array[j] = (t_point *)malloc(sizeof(t_point) * data->size_x);
		i = 0;
		while (i < data->size_x)
		{
			array[j][i].alt = (*prev_array)[j][i].alt;
			array[j][i].has_color = (*prev_array)[j][i].has_color;
			array[j][i].color = (*prev_array)[j][i].color;
			i++;
		}
		j++;
	}
	while (j < data->capacity_y)
	{
		array[j] = (t_point *)malloc(sizeof(t_point) * data->size_x);
		i = 0;
		while (i < data->size_x)
		{
			array[j][i].alt = 0;
			array[j][i].has_color = 0;
			array[j][i].color = 0;
			i++;
		}
		j++;
	}
	j = 0;
	while (j < data->size_y)
	{
		ft_memdel((void **)prev_array[j]);
		j++;
	}
	if (prev_array)
		ft_memdel((void **)prev_array);
	return (array);
}

t_point	**read2(const int fd, t_data *data)
{
	size_t	i;
	size_t	length;
	char	*line;
	char	**split;
	t_point	**points;
	
	data->size_y = 0;
	points = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		data->size_x = ft_2d_strlen(split);
		if (data->size_y == 0)
		{
			length = data->size_x;
			data->capacity_y = length;
			points = new_array(&points, data);
		}
		if (data->size_x != length)
			ft_putendl("len error");
		if (data->size_y > data->capacity_y)
		{
			data->capacity_y *= 2;
			points = new_array(&points, data);
		}
		i = 0;
		while (i < data->size_x)
		{
		//	printf("(read2)split[i] = |%s|\n", split[i]);
		//	printf("%d ---- %d\n", i, j);
			if (valid_nbr(split[i], &points, i, data->size_y) == 0)
			{
				ft_putendl("invalid nbr error");
				exit(0);
			}
			if (valid_color(split[i], &points, i, data->size_y) == 0)
			{
				ft_putendl("invalid color error");
				exit(0);
			}
			i++;
		}
		data->size_y++;
	}
	return (points);
}
