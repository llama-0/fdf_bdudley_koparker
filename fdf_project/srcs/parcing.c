/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:47:52 by koparker          #+#    #+#             */
/*   Updated: 2019/09/25 23:05:42 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void			error_message(int index, t_data *data, char **str, char *line)
{
	if (index == 0)
		ft_putendl_fd("Invalid data format", 2);
	else if (index == 1)
		ft_putendl_fd("Invalid color", 2);
	else if (index == 2)
		ft_putendl_fd("Invalid line length", 2);
	else if (index == 3)
		ft_putendl_fd("Memory allocation failed\n", 2);
	else if (index == 4)
		perror(NULL);
	if (data && data->arr)
		delete_array(data);
	if (str)
		ft_free_char_arr(&str);
	if (line)
		ft_strdel(&line);
	exit(1);
}

void			size_array(t_data *data, size_t length,
				char **split, char *line)
{
	if (data->size_y == 0)
	{
		data->size_x = length;
		data->capacity_y = length;
	}
	else
		data->capacity_y *= 2;
	data->arr = new_array(&(data->arr), data, split, line);
}

t_point			**read_file(const int fd, t_data *data)
{
	size_t	i;
	char	*line;
	char	**split;

	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		i = ft_2d_strlen(split);
		if (data->size_y >= data->capacity_y)
			size_array(data, i, split, line);
		if (data->size_x != i)
			error_message(2, data, split, line);
		i = -1;
		while (++i < data->size_x)
		{
			if (valid_nbr(split[i], data, i, data->size_y) == 0)
				error_message(0, data, split, line);
			if (valid_color(split[i], data, i, data->size_y) == -1)
				error_message(1, data, split, line);
		}
		data->size_y++;
		ft_free_char_arr(&split);
		ft_strdel(&line);
	}
	return (data->arr);
}

void			coord_to_pixel(t_data *data)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < data->size_y)
	{
		i = 0;
		while (i < data->size_x)
		{
			(data->arr)[j][i].x = (i * data->step -
					data->step * data->size_x / 2);
			(data->arr)[j][i].y = (j * data->step -
					data->step * data->size_y / 2);
			(data->arr)[j][i].z = -((data->arr)[j][i].alt * data->step);
			i++;
		}
		j++;
	}
}
