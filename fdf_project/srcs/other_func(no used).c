/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func(no used).c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:11:59 by koparker          #+#    #+#             */
/*   Updated: 2019/09/22 20:26:03 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

//    j = 0;
//    while (j < data->size_y)
//    {
//        i = 1;
//        while (i < data->size_x) {
//        //    printf("POPO\n");
//            printf("x, y %d %d\n", (*head)[j][i].x, (*head)[j][i].y);
//            iso(&(*head)[j][i].x, &(*head)[j][i].y);
//            printf("x, y %d %d\n", (*head)[j][i].x, (*head)[j][i].y);
//            i++;
//        }
//        j++;
//    }

//    int previous_x;
//    int previous_y;
//
//    previous_x = (*head)[0][1].x;
//    previous_y = (*head)[0][1].y;
//    (*head)[0][1].x = previous_x * cos(5.75959) - previous_y * sin(5.75959);
//    (*head)[0][1].y = previous_y * cos(5.75959) + previous_x * sin(5.75959);



//    printf("step`-x |%d|\n", step_x);
//    printf("step`-y |%d|\n", step_y);
//    (void)head;
//    while (j < DH)
//    {
//        i = 0;
//        while (i < DW)
//        {
//            if ((i % step_x == 0 || j % step_y == 0)
//            && ((size_t)j)<= ((data->size_y - 1) * (step_y))
//            && ((size_t)i)<= ((data->size_x - 1)* (step_x)))
//            {
//              //  draw_line(&((*head)[j / step_y][i / step_x]), &((*head)[j / step_y][i / step_x]))
//                if ((*head)[j / step_y][i / step_x].alt != 0)
//                    (*img_arr)[j * DW + i] = 0xFFFFF;
//                else
//                    (*img_arr)[j * DW + i] = (*head)[j / step_y][i / step_x].color;
//            printf("i = %d - d %lu\n j = %d - d %lu\n", i,((data->size_x - 1)* (step_x)) , j , ((data->size_y - 1) * (step_y)));
//            }
//            i++;
//        }
//        j++;
//    }
//    step_y = DH / data->size_y;


static void iso(int *x, int *y)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(0.523599) - previous_y * sin(0.523599);
	*y = previous_y * cos(0.523599) + previous_x * sin(0.523599);
}

static void riso(int *x, int *y)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(5.75959) - previous_y * sin(5.75959);
	*y = previous_y * cos(5.75959) + previous_x * sin(5.75959);
}


int		parse_line(char ***split, int **data)
{
	int		j;

	j = 0;
	while (split[0][j])
	{
		if (valid_nbr(split[0][j], &(*data)[j]) == 0)
			return (0);
		if (valid_color(split[0][j], &(*color)[j] == 0)
			return (0);
		j++;
	}
	return (1);
}

void	free_struct(t_data **map, int i)
{
	int	j;

	j = 0;
	if ((*map)->data && (*map)->data[j])
	{
		while (j < i)
		{
			free((*map)->data[j]);
			(*map)->data[j] = NULL;
			j++;
		}
	}
	if ((*map)->data)
	{
		free((*map)->data);
		(*map)->data = NULL;
	}
	free(*map);
	*map = NULL;
	exit(0);
}

t_data	*read_data2(const int fd)
{
	char	**split;

	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
	}
}

t_data	*read_data(const int fd)
{
	int		i;
	t_data	*map;
	char	*line;
	char	**split;

	i = 0;
	if ((map = (t_data *)malloc(sizeof(t_data))) == NULL)
		exit(0);
	map->data = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		map->len = ft_2d_strlen(split);
		if (i == 0)
			map->length = map->len;
		if (map->len != map->length)
			free_struct(&map, i);
		if (map->data == NULL)
		{
			if ((map->data = (int **)malloc(sizeof(int *) * map->len)) == NULL)
				free_struct(&map, i);
		}
		if ((map->data[i] = (int *)malloc(sizeof(int) * map->len)) == NULL)
			free_struct(&map, i);
		ft_memset(map->data[i], 0, map->len);
		if (parse_line(&split, &(map->data[i])) == 0)
			free_struct(&map, i);
		i++;
	}
	map->height = i;
	return (map);
}



//GRADIENT TMP
// t_gradient	fn1(t_point *p, int mid, int current, int flag)
// {
// 	t_gradient	gr;
// 	int			percentage;
// 	int			coord;

// 	(flag == 0) ? (coord = p->x) : (coord = p->y);
// 	percentage = percent(coord, mid, current, flag);
// 	gr.red = get_light((p->color >> 16) & 0xFF, (COLOR_MID >> 16) & 0xFF, percentage);
// 	gr.green = get_light((p->color >> 8) & 0xFF, (COLOR_MID >> 8) & 0xFF, percentage);
// 	gr.blue = get_light((p->color) & 0xFF, (COLOR_MID) & 0xFF, percentage);
// 	return (gr);
// }

// t_gradient	fn2(int mid, t_point *p, int current, int flag)
// {
// 	t_gradient	gr;
// 	int			percentage;
// 	int			coord;

// 	(flag == 0) ? (coord = p->x) : (coord = p->y);
// 	percentage = percent(mid, coord, current, flag);
// 	gr.red = get_light((p->color >> 16) & 0xFF, (COLOR_MID >> 16) & 0xFF, percentage);
// 	gr.green = get_light((p->color >> 8) & 0xFF, (COLOR_MID >> 8) & 0xFF, percentage);
// 	gr.blue = get_light((p->color) & 0xFF, (COLOR_MID) & 0xFF, percentage);
// 	return (gr);
// }

// int				get_color(t_point *p1, t_point *p2, int current)
// {
// 	t_gradient	gr;
// 	int			tmp;
// 	int			middle;

// 	// printf("color_1 = %d, color_2 = %d\n", p1->color, p2->color);
// 	gr.delta = p2->x - p1->x;
// 	tmp = p2->y - p1->y;
// 	if (gr.delta > tmp)
// 		tmp = 0;
// 	else
// 	{
// 		gr.delta = tmp;
// 		tmp = 1;
// 	}
// 	if (p1->color == p2->color)
// 		return (p1->color);
// 	if (tmp == 0)
// 	{
// 		if (current < ((middle = gr.delta / 2 + p1->x) + SHIFT_X))
// 			fn1(p1, middle, current, tmp);
// 		else
// 			fn2(middle, p2, current, tmp);
// 	}
// 	else
// 	{
// 		if (current < ((middle = gr.delta / 2 + p1->y) + SHIFT_Y))
// 			fn1(p1, middle, current, tmp);
// 		else
// 			fn2(middle, p2, current, tmp);
// 	}
// 	return ((gr.red << 16) | (gr.green << 8) | gr.blue);
// }