/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/10 17:50:45 by koparker         ###   ########.fr       */
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
	//lst = head;
/*	while (lst != NULL)
	{
		printf("alt %d\n", lst->content->alt);
		lst = lst->next;
	}
*/	return (0);
}
