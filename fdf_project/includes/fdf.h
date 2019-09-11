/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:13:28 by koparker          #+#    #+#             */
/*   Updated: 2019/09/11 17:55:27 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
#define  DW 600
#define DH 600
# define COLOR_DEFAULT 0xFFFFFF

typedef struct		s_point
{
//	double			x;
//	double			y;
	int				alt;
	int				has_color; // default 0 (no color)
	int				color;
}					t_point;

typedef struct			s_data
{
//	size_t				capacity_x; //max
	size_t				size_x; //use
	size_t				capacity_y;
	size_t				size_y;
}						t_data;


int		valid_nbr(char *spl, t_point ***point, int i, int j);
int		valid_color(char *spl, t_point ***point, int i, int j);
int		ft_atoi_hex(char *s);
//int		parse_line(char ***split, int **data);
//t_data	*read_data(const int fd);
t_point	**read2(const int fd, t_data *data);
void	print(t_point **points, t_data *data);

#endif
