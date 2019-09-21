/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:42:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/18 20:44:10 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void rotate_OZ(int *x, int *y, size_t rotate)
{
	int previous_x;
	int previous_y;

	previous_x = *x - DW / 2;
	previous_y = *y - DH / 2;
	*x = trunc((previous_x * COS(rotate)) - trunc(previous_y * SIN(rotate))) + DW / 2;
	*y = trunc((previous_y * COS(rotate)) + trunc(previous_x * SIN(rotate))) + DH / 2;
}

//static void rotate_OY(int *x, int *y,  size_t rotate)
//{
//	int previous_x;
//	int previous_y;
//
//	previous_x = *x;
//	previous_y = *y;
//	*x = (previous_x - previous_y) * COS(30);
//	*y = -z + (previous_x + previous_y) * SIN(30);
//}
//
//static void rotate_OX(int *x, int *y, size_t rotate)
//{
//	int previous_x;
//	int previous_y;
//
//	previous_x = *x;
//	previous_y = *y;
//	*x = (previous_x - previous_y) * COS(30);
//	*y = -z + (previous_x + previous_y) * SIN(30);
//}

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
       		rotate_OZ(&(data->arr)[j][i].x, &(data->arr)[j][i].y, data->rotate_z);
			i++;
      	}
       	j++;
   	}
}