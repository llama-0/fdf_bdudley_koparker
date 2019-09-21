/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:42:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/21 20:05:33 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void rotate_OX(int *y, int *z, size_t rotate)
{
	int previous_y;
	int previous_z;

	previous_y = *y;
	previous_z = *z;
	*y = previous_y * COS(rotate) + previous_z * SIN(rotate);
	*z = -previous_y * SIN(rotate) + previous_z * COS(rotate);
}

static void rotate_OY(int *x, int *z,  int centre, size_t rotate)
{
	int previous_x;
	int previous_z;

	previous_x = *x;
	previous_z= *z;
	*x = previous_x * COS(rotate) + previous_z * SIN(rotate);
	*z = previous_z * COS(rotate) - previous_x * SIN(rotate) + centre;
}

static void rotate_OZ(int *x, int *y, int centre, size_t rotate)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = trunc((previous_x * COS(rotate)) - trunc(previous_y * SIN(rotate))) + centre;
	*y = trunc((previous_y * COS(rotate)) + trunc(previous_x * SIN(rotate))) + centre;
}

// TODO: add rotation_OX, rotation_OY; remove iso. 
void	apply_rotation(t_data *data)
{
	size_t	i;
	size_t	j;

	j = 0;
   	while (j < data->size_y)
   	{
       	i = 0;
       	while (i < data->size_x)
		{
       		rotate_OX(&(data->arr)[j][i].y, &(data->arr)[j][i].z, data->rotate_x);
       		rotate_OY(&(data->arr)[j][i].x, &(data->arr)[j][i].z, 0, data->rotate_y);
       		rotate_OZ(&(data->arr)[j][i].x, &(data->arr)[j][i].y, 0, data->rotate_z);

			i++;
      	}
       	j++;
   	}
}