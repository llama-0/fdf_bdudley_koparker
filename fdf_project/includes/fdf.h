/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:13:28 by koparker          #+#    #+#             */
/*   Updated: 2019/09/15 15:08:37 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>

# define DW 50
# define DH 50

typedef struct			s_point
{
	int					x;
	int					y;
	int					alt;
	int					has_color; // default 0 (no color)
	int					color;
}						t_point;

typedef struct			s_data
{
	size_t				size_x;
	size_t				capacity_y;
	size_t				size_y;
}						t_data;

typedef struct			s_window
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	int					*img_arr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
}						t_window;

int						valid_nbr(char *spl, t_point ***point, int i, int j);
int						valid_color(char *spl, t_point ***point, int i, int j);
int						ft_atoi_hex(char *s);
t_point					**read_file(const int fd, t_data *data);
void					print(t_point **points, t_data *data);

t_point					**new_array(t_point		***prev_array, t_data	*data);
void					delete_array(t_point		***prev_array, t_data	*data);
void					init_array(t_point		***array, t_data	*data, int j, int i);
void					coord_to_pixel(t_point ***arr, t_data *data);

void					error_message(int index, t_point ***points, t_data	*data, char ***str);
#endif
