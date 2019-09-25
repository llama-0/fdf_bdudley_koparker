/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:10:37 by koparker          #+#    #+#             */
/*   Updated: 2019/09/22 18:17:26 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

// TODO: check number 9e,0xff -> 0 and e,0xff -> 0. Stop validation or replace all with 0's ??
int	valid_nbr(char *spl, t_data *data, int i, int j)
{
	int		n;
	char	*tmp;
	char	*t;

	tmp = spl;
	t = ft_strchr(spl, ',');
	n = ft_atoi(tmp);
	if (n == 0)
	{
		if (t == NULL)
		{
			if (ft_strcmp(spl, "0") != 0)
				return (0);
		}
		else if (t - spl != 1)
		{
			t = NULL;
			return (0);
		}
	}
	(data->arr)[j][i].x = i;
	(data->arr)[j][i].y = j;
	(data->arr)[j][i].alt = n;
	return (1);
}

int	valid_color(char *spl, t_data *data, int i, int j)
{
	int		color;
	char	*tmp;

	tmp = spl;
	((data->arr)[j][i].alt == 0) ? ((data->arr)[j][i].color = DEFAULT) :
		((data->arr)[j][i].color = COLOR_HIGH);
	if ((tmp = ft_strchr(spl, ',')) != NULL)
	{
		if ((color = ft_atoi_hex(tmp + 1)) == 0)
			return (0);
		(data->arr)[j][i].color = color;
		return (1);
	}
	return (1);
}
