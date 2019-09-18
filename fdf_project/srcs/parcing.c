/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:47:52 by koparker          #+#    #+#             */
/*   Updated: 2019/09/18 17:47:11 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void		error_message(int index, t_point ***points, t_data	*data, char ***str)
{
	if (index == 0)
		ft_putendl("Invalid altitude in the cart");
	else if (index == 1)
		ft_putendl("Invalid color in the cart");
	else if (index == 2)
		ft_putendl("Invalid length cart");
	else if (index == 3)
		perror("Memory allocation failed\n");
	delete_array(points, data);
	//TODO: delete split
	exit(1);

}

void		size_array(t_point ***points, t_data *data, size_t length)
{
	if (data->size_y == 0)
	{
		data->size_x = length;
		data->capacity_y = length;
	}
	else
		data->capacity_y *= 2;
	*points = new_array(points, data);
}

t_point		**read_file(const int fd, t_data *data)
{
	size_t	i;
	char	*line;
	char	**split;
	t_point	**points;

	points = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		i = ft_2d_strlen(split);
		if (data->size_y >= data->capacity_y)
			size_array(&points, data, i);
		if (data->size_x != i)
			error_message(2, &points, data, &split);
		i = -1;
		while (++i < data->size_x)
		{
			if (valid_nbr(split[i], &points, i, data->size_y) == 0)
				error_message(0, &points, data, &split);
			if (valid_color(split[i], &points, i, data->size_y) == 0)
				error_message(1, &points, data, &split);
		}
		data->size_y++;
	}
	return (points);
}

void	coord_to_pixel(t_point ***arr, t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	step_x;
	size_t	step_y;
	size_t	delta_x;
	size_t	delta_y;

	step_x = (data->size_x > 1) ? (DW - 1) / (data->size_x - 1) : DW - 1;
	step_y = (data->size_y > 1) ? (DH - 1) / (data->size_y - 1) : DH - 1;
	j = 0;
	while (j < data->size_y)
	{
		i = 0;
		while (i < data->size_x)
		{
			(*arr)[j][i].x *= step_x;
			(*arr)[j][i].y *= step_y;
			i++;
		}
		j++;
	}
}

void	shift_coords(int *x, int *y, int shift)
{
	*x += shift;
	*y += shift; 
}