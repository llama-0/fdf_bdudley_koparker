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

static void rotate_OZ(int *x, int *y)
{
	int previous_x;
	int previous_y;

	previous_x = *x - DW / 2;
	previous_y = *y - DH / 2;
	*x = trunc((previous_x * COS(ALPHA)) - trunc(previous_y * SIN(ALPHA))) + DW / 2;
	*y = trunc((previous_y * COS(ALPHA)) + trunc(previous_x * SIN(ALPHA))) + DH / 2;
}

// TODO: add rotation_OX, rotation_OY; remove iso. 
void	apply_rotation(t_data *data, int keycode)
{
	size_t	i;
	size_t	j;

	j = 0;
   	while (j < data->size_y)
   	{
       	i = 0;
       	while (i < data->size_x)
		{
        	if (keycode == 6)
				rotate_OZ(&(data->arr)[j][i].x, &(data->arr)[j][i].y);
			i++;
      	}
       	j++;
   	}
}