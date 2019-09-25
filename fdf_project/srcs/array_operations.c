/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 11:53:46 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/23 19:24:47 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void			init_array(t_point ***array, t_data *data, size_t j, size_t i)
{
	while (j < data->capacity_y)
	{
		(*array)[j] = (t_point *)malloc(sizeof(t_point) * data->size_x);
		i = 0;
		while (i < data->size_x)
		{
			(*array)[j][i].alt = 0;
			(*array)[j][i].color = 0;
			(*array)[j][i].x = 0;
			(*array)[j][i].y = 0;
			i++;
		}
		j++;
	}
}

void			delete_array(t_data *data)
{
	size_t		j;

	j = 0;
	while (j < data->size_y)
	{
		free((data->arr)[j]);
		(data->arr)[j] = NULL;
		j++;
	}
	if (data->arr)
		free((data->arr));
}

t_point			**new_array(t_point ***prev_array,
				t_data *data, char **split, char *line)
{
	t_point	**array;
	size_t	j;
	size_t	i;

	j = 0;
	if (!(array = (t_point **)malloc(sizeof(t_point *) * data->capacity_y)))
		error_message(3, data, split, line);
	while (j < data->size_y)
	{
		if (!(array[j] = (t_point *)malloc(sizeof(t_point) * data->size_x)))
			error_message(3, data, split, line);
		i = 0;
		while (i < data->size_x)
		{
			array[j][i].alt = (*prev_array)[j][i].alt;
			array[j][i].color = (*prev_array)[j][i].color;
			array[j][i].x = (*prev_array)[j][i].x;
			array[j][i].y = (*prev_array)[j][i].y;
			i++;
		}
		j++;
	}
	init_array(&array, data, j, i);
	delete_array(data);
	return (array);
}
