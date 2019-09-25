/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:42:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/23 23:00:53 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	rotate_ox(int *y, int *z, size_t rotate)
{
	int previous_y;
	int previous_z;

	previous_y = *y;
	previous_z = *z;
	*y = previous_y * COS(rotate) + previous_z * SIN(rotate);
	*z = -previous_y * SIN(rotate) + previous_z * COS(rotate);
}

static void	rotate_oy(int *x, int *z, size_t rotate)
{
	int previous_x;
	int previous_z;

	previous_x = *x;
	previous_z = *z;
	*x = previous_x * COS(rotate) + previous_z * SIN(rotate);
	*z = previous_z * COS(rotate) - previous_x * SIN(rotate);
}

static void	rotate_oz(int *x, int *y, size_t rotate)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = trunc((previous_x * COS(rotate)) - trunc(previous_y * SIN(rotate)));
	*y = trunc((previous_y * COS(rotate)) + trunc(previous_x * SIN(rotate)));
}

void		apply_rotation(t_data *data)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < data->size_y)
	{
		i = 0;
		while (i < data->size_x)
		{
			rotate_ox(&(data->arr)[j][i].y, &(data->arr)[j][i].z,
					data->rotate_x);
			rotate_oy(&(data->arr)[j][i].x, &(data->arr)[j][i].z,
					data->rotate_y);
			rotate_oz(&(data->arr)[j][i].x, &(data->arr)[j][i].y,
					data->rotate_z);
			(data->arr)[j][i].x *= 1 + data->scale;
			(data->arr)[j][i].y *= 1 + data->scale;
			(data->arr)[j][i].z *= 1 + data->scale;
			i++;
		}
		j++;
	}
}
