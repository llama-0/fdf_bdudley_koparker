/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 11:53:46 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/18 18:34:08 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void		init_array(t_point ***array, t_data	*data, int j, int i)
{
	while (j < data->capacity_y)
	{
		(*array)[j] = (t_point *)malloc(sizeof(t_point) * data->size_x);
		i = 0;
		while (i < data->size_x)
		{
			(*array)[j][i].alt = 0;
			(*array)[j][i].has_color = 0;
			(*array)[j][i].color = 0;
			(*array)[j][i].x = 0;
			(*array)[j][i].y = 0;
			i++;
		}
		j++;
	}
}

void		delete_array(t_data	*data)
{
	int		j;

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

// TODO: add split to arg list. Reason - to free it, if smth fails
t_point		**new_array(t_point		***prev_array, t_data	*data)
{
	t_point	**array;
	size_t	j;
	size_t	i;

	j = 0;
	if (!(array = (t_point **)malloc(sizeof(t_point *) * data->capacity_y)))
		error_message(3, data, NULL);
	while (j < data->size_y)
	{
		if (!(array[j] = (t_point *)malloc(sizeof(t_point) * data->size_x)))
			error_message(3, data, NULL);
		i = 0;
		while (i < data->size_x)
		{
			array[j][i].alt = (*prev_array)[j][i].alt;
			array[j][i].has_color = (*prev_array)[j][i].has_color;
			array[j][i].color = (*prev_array)[j][i].color;
			array[j][i].x = (*prev_array)[j][i].x;
			array[j][i].y = (*prev_array)[j][i].y;
			i++;
		}
		j++;
	}
	init_array(&array, data, j , i);
	delete_array(data);
	return (array);
}
