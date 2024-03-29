/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:13:28 by koparker          #+#    #+#             */
/*   Updated: 2019/09/25 18:33:54 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>

# define DW 500
# define DH 500

# define DW_IM (DW * 2)
# define DH_IM (DH * 2)

# define SHIFT_X DW
# define SHIFT_Y DH

# define ISO 1
# define CONIC 2
# define NO_PROJECTION 0

# define SIN(x) sin(x * M_PI/180)
# define COS(x) cos(x * M_PI/180)

# define ALPHA 30
# define SCALE 0.2
# define M_STEP 20
# define M_X DW_IM * 5 / 8
# define M_Y DH_IM * 3 / 4

# define DEFAULT 0xFFFFFF
# define COLOR_HIGH 0xFF0000
# define COLOR_MID 0x00FF00
# define BLACK 0x000000
# define COLOR_TABLE 0xFFFFFF

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					alt;
	int					color;
}						t_point;

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

typedef struct			s_data
{
	size_t				size_x;
	size_t				capacity_y;
	size_t				size_y;
	size_t				step;
	double				camera;
	int					projection;
	double				scale;
	size_t				rotate_x;
	size_t				rotate_y;
	size_t				rotate_z;
	void				*ptr;
	t_point				**arr;
	t_window			win;
}						t_data;

typedef struct			s_draw_line
{
	double				diff;
	int					dx;
	int					dy;
	int					y_i;
	int					x_i;
	int					y;
	int					x;
}						t_draw_line;

typedef struct			s_gradient
{
	int					red;
	int					green;
	int					blue;
	int					delta;
	int					flag;
}						t_gradient;

int						valid_nbr(char *spl, t_data *data, int i, int j);
int						valid_color(char *spl, t_data *data, int i, int j);
int						ft_atoi_hex(char *s);
t_point					**read_file(const int fd, t_data *data);

t_point					**new_array(t_point ***prev_array, t_data *data,
						char **split, char *line);
void					delete_array(t_data	*data);
void					init_array(t_point ***array, t_data *data,
						size_t j, size_t i);
void					coord_to_pixel(t_data *data);

void					new_image(t_data *data);
void					draw_plane(t_data *data, int **img_arr);
void					apply_rotation(t_data *data);
void					apply_projection(t_data *data);

void					balance_delta_for_color(t_point *p1, t_point *p2,
						t_gradient *gr);
int						get_color(t_point *p1, t_point *p2, int current);

void					error_message(int index, t_data	*data,
						char **str, char *line);
int						key_release(int keycode, void *param);
int						mlx_close(void *param);
int						get_max_z(t_data *data);
#endif
