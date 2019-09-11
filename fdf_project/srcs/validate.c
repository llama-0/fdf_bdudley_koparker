/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:10:37 by koparker          #+#    #+#             */
/*   Updated: 2019/09/11 14:43:03 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	valid_nbr(char *spl, t_point ***point, int i, int j)
{
	int		n;
	char    *tmp;

	tmp = spl;			   
	n = ft_atoi(tmp);
//	printf("atoi check = |%d|\n", n);		
	if (n == 0)
	{
		if (ft_strcmp(spl, "0") == 0)
		{
			(*point)[j][i].alt = n;
	 		// (*point)->y = j;
			// (*point)->alt = n;
			return (1);
		}
		else
			return (0);
	}
	// (*point)->x = i;
	// (*point)->y = j;
	// (*point)->alt = n;
	(*point)[j][i].alt = n;
//	printf("(*point)->alt = %d\n", (*point)->alt);
	return (1);
}

int	valid_color(char *spl, t_point ***point, int i, int j)
{
	int		color;
	char	*tmp;

	color = 0;
	tmp = spl;
    (*point)[j][i].color = 0xFFFFFF;
//	if ((tmp = ft_strchr(spl, ',')) != NULL)
//	{
//		//if ((color = ft_atoi_hex(tmp)) == 0)
//		//	return (0);
//		(*point)[j][i].color = 0xFFFFFF;
//		return (1);
//	}
//	else
//	{
//		//(*point)->has_color = 0;
//		(*point)[j][i].color = 0;
//		return (1);
//	}
	return (1); //return (0);
}
