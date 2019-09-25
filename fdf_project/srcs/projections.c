/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:43:46 by koparker          #+#    #+#             */
/*   Updated: 2019/09/22 19:38:16 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static int	get_max_z(t_data *data)
{
	size_t	i;
	size_t	j;
	int		max;

	j = 0;
	max = (data->arr)[0][0].z;
	while (j < data->size_y)
	{
		i = 0;
		while (i < data->size_x)
		{
			if (max < (data->arr)[j][i].z)
				max = (data->arr)[j][i].z;
			i++;
		}
		j++;
	}
	return (max);
}

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x + previous_y) * (COS(30));
    *y = z + (previous_x - previous_y) * (-SIN(30));
}

 static void perspective(int *x, int *y, int *z, int max_z)
 {
	 int previous_x;
	 int previous_y;
	 int previous_z;
	 double camera;

	 camera = 50 + max_z;
	 if (camera == 0)
	 	camera = 1;
	 previous_x = *x;
	 previous_y = *y;
	 previous_z = *z;
	 *x = trunc(previous_x * (1 - previous_z / camera));
	 *y = trunc(previous_y * (1 - previous_z / camera));
	 *z = max_z;
	// *z = trunc(previous_z * (1 - previous_z / camera));
 }

void	apply_projection(t_data *data)
{
	size_t	i;
	size_t	j;
	int 	max_z;

	j = 0;
	max_z = get_max_z(data);
   	while (j < data->size_y)
   	{
       	i = 0;
       	while (i < data->size_x)
		{
			if (data->camera == ISO)
				iso(&(data->arr)[j][i].x, &(data->arr)[j][i].y, (data->arr)[j][i].z);
			else if (data->camera == CONIC)
				perspective(&(data->arr)[j][i].x, &(data->arr)[j][i].y, &(data->arr)[j][i].z, max_z);
			(data->arr)[j][i].x *= 1 + data->scale;
			(data->arr)[j][i].y *= 1 + data->scale;
			(data->arr)[j][i].z *= 1 + data->scale;
			i++;
      	}
       	j++;
   	}
}