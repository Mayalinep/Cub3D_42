/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:45:00 by mpelage           #+#    #+#             */
/*   Updated: 2025/07/01 17:54:41 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
int	check_corner_collision(double new_x, double new_y, t_parsed_data *data)
{
	int	old_x;
	int	old_y;
	int	new_map_x;
	int	new_map_y;

	old_x = (int)data->player_x;
	old_y = (int)data->player_y;
	new_map_x = (int)new_x;
	new_map_y = (int)new_y;
	if ((new_map_x != old_x || new_map_y != old_y) && (new_map_x != old_x
			&& new_map_y != old_y))
	{
		if (new_map_x > old_x && new_map_y < old_y)
		{
			if (new_map_x - 1 >= 0 && data->map[new_map_y][new_map_x - 1] == '1'
				&& new_map_y + 1 < data->map_height 
				&& data->map[new_map_y + 1][new_map_x] == '1')
				return (1);
		}
		else if (new_map_x > old_x && new_map_y > old_y)
		{
			if (new_map_x - 1 >= 0 && data->map[new_map_y][new_map_x - 1] == '1'
				&& new_map_y - 1 >= 0 
				&& data->map[new_map_y - 1][new_map_x] == '1')
				return (1);
		}
		else if (new_map_x < old_x && new_map_y < old_y)
		{
			if (new_map_x + 1 < data->map_width 
				&& data->map[new_map_y][new_map_x + 1] == '1'
				&& new_map_y + 1 < data->map_height 
				&& data->map[new_map_y + 1][new_map_x] == '1')
				return (1);
		}
		else if (new_map_x < old_x && new_map_y > old_y)
		{
			if (new_map_x + 1 < data->map_width 
				&& data->map[new_map_y][new_map_x + 1] == '1'
				&& new_map_y - 1 >= 0 
				&& data->map[new_map_y - 1][new_map_x] == '1')
				return (1);
		}
	}
	return (0);
}
*/

int	is_too_close_to_wall(double x, double y, t_parsed_data *data, double margin)
{
	int	check_x;
	int	check_y;
	int	map_x;
	int	map_y;

	check_y = -1;
	while (check_y <= 1)
	{
		check_x = -1;
		while (check_x <= 1)
		{
			map_x = (int)(x + check_x * margin);
			map_y = (int)(y + check_y * margin);
			if (map_x < 0 || map_x >= data->map_width || map_y < 0
				|| map_y >= data->map_height)
				return (1);
			if (data->map[map_y][map_x] == '1')
				return (1);
			check_x++;
		}
		check_y++;
	}
	return (0);
}

int	wall_collision(double new_x, double new_y, t_parsed_data *data)
{
	double	margin;

	margin = 0.2;
	if (new_y < margin || new_y >= data->map_height - margin || new_x < margin
		|| new_x >= data->map_width - margin)
		return (1);
	if (data->map[(int)new_y][(int)new_x] == '1')
		return (1);
	if (is_too_close_to_wall(new_x, new_y, data, margin))
		return (1);
	return (0);
} 