/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:10:37 by koparker          #+#    #+#             */
/*   Updated: 2019/09/18 20:57:30 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	valid_nbr(char *spl, t_data *data, int i, int j)
{
	int		n;
	char	*tmp;

	tmp = spl;
	n = ft_atoi(tmp);
	if (n == 0)
	{
		if (ft_strcmp(spl, "0") != 0)
			return (0);
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
    (data->arr)[j][i].color = DEFAULT;
    (data->arr)[j][i].has_color = 0;
	printf("|%s|\n", tmp);
	if ((tmp = ft_strchr(spl, ',')) != NULL)
	{
		if ((color = ft_atoi_hex(tmp + 1)) == 0)
			return (0);
        (data->arr)[j][i].color = color;
		return (1);
	}
	return (1);
}
