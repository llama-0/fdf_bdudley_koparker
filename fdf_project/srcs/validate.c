/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:10:37 by koparker          #+#    #+#             */
/*   Updated: 2019/09/18 18:41:22 by bdudley          ###   ########.fr       */
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
    (data->arr)[j][i].color = 0xFFFFFF;
    (data->arr)[j][i].has_color = 0;
	if ((tmp = ft_strchr(spl, ',')) != NULL)
	{
		if ((color = ft_atoi_hex(tmp)) == 0)
		{
			printf("I ne znau color |%d|", color); //delete
			return (0);
		}
        (data->arr)[j][i].color = color;
		return (1);
	}
	return (1);
}
