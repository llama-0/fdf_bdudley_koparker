/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/10 23:33:52 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	print(t_point **points, t_data *data)
{
	for (size_t j = 0; j < data->size_y; j++)
	{
		for (size_t i = 0; i < data->size_x; i++)
		{
			printf("%d ", points[j][i].alt);
		}
		printf("\n");
	}
}

void    find_open()
{
    void *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    int     *img_arr;
    int bits_per_pixel;
    int size_line;
    int endian;
    int i;
    int j;

    bits_per_pixel = 0;
    size_line = 0;
    endian = 0;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 600, 600, "Koparker");
    img_ptr = mlx_new_image(mlx_ptr, 600, 600);
    img_arr = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
    i = 0;
    while (i < 600)
    {
        j = 0;
        while (j < 600)
        {
            img_arr[i*600 + j] = 0xFFFFFF;
            j++;
        }
        i++;
    }
    mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, 0, 0 );
    mlx_loop(mlx_ptr);
}


int main(int ac, char **av)
{
	int		fd;
	t_point	**head;
	t_data	data;
	//t_list	*lst;

	(void)ac;//
	if ((fd = open(av[1], O_RDONLY)) >= 0)
	{
		head = read2(fd, &data);
		print(head, &data);
		close(fd);
	}
	else
	{
		perror("open: couldn't open the file\n");
		return (0);
	}
	find_open();
	//lst = head;
/*	while (lst != NULL)
	{
		printf("alt %d\n", lst->content->alt);
		lst = lst->next;
	}
*/	return (0);
}
