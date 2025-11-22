#include "cub3d.h"

static void put_marks(char **cp_map, int x, int y)
{
    cp_map[y][x] = '*';

    if (y > 0 && cp_map[y - 1][x] && cp_map[y - 1][x] != '1' && cp_map[y - 1][x] != '*')
        put_marks(cp_map, x, y - 1);
    if (cp_map[y + 1] && cp_map[y + 1][x] && cp_map[y + 1][x] != '1' && cp_map[y + 1][x] != '*')
        put_marks(cp_map, x, y + 1);
    if (x > 0 && cp_map[y][x - 1] && cp_map[y][x - 1] != '1' && cp_map[y][x - 1] != '*')
        put_marks(cp_map, x - 1, y);
    if (cp_map[y][x + 1] && cp_map[y][x + 1] != '1' && cp_map[y][x + 1] != '*')
        put_marks(cp_map, x + 1, y);
}

bool space_chk(int x, int y, char **cp_map)
{
    if (cp_map[x][y] == '*')
    {
        if (x == 0 || y == 0 || cp_map[x + 1] == NULL || cp_map[x][y + 1] == '\0')
            return (false);
        if (cp_map[x + 1][y] != '1' && cp_map[x + 1][y] != '*')
            return (false);
        if (cp_map[x - 1][y] != '1' && cp_map[x - 1][y] != '*')
            return (false);
        if (cp_map[x][y + 1] != '1' && cp_map[x][y + 1] != '*')
            return (false);
        if (cp_map[x][y - 1] != '1' && cp_map[x][y - 1] != '*')
            return (false);
    }
    return (true);
}

bool	wall_check(t_map_chk *info)
{
	int		x;
	int		y;
	char	**cp_map;

	x = 0;
	y = 0;
	cp_map = map_copy(info->map);
	put_marks(cp_map, info->p_x, info->p_y);
	while (cp_map[x])
	{
		y = 0;
		while (cp_map[x][y])
		{
			if(!space_chk(x, y, cp_map))
			{
				free_dp(cp_map);
				printf("Error : Invalid map\n");
				return(false);
			}
			if (cp_map[x][y] != '1' && cp_map[x][y] != '*'
				&& cp_map[x][y] != '\n' && cp_map[x][y] != '\0'
				&& cp_map[x][y] != '0' && cp_map[x][y] != ' ')
			{
				free_dp(cp_map);
				printf("Error : Invalid map\n");
				return(false);
			}
			y++;
		}
		x++;
	}
	free_dp(cp_map);
	return(true);
}

bool	player_chk(t_map_chk *info)
{
	int c = 0;
	int i = 0;
	int j = 0;

	char **map = info->map;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S'
				|| map[i][j] == 'W')
			{
				info->p_x = j;
				info->p_y = i;
				c++;
			}
			j++;
		}
		i++;
	}
	if(c == 0)
	{
		printf("No player start position\n");
		return(false);
	}
	else if(c > 1)
	{
		printf("Multiple player start positions");
		return(false);
	}
	else if(info->p_x == 0 || info->p_y == 0)
	{
		printf("Player on the edge\n");
		return(false);
	}
	else
		return(true);
}

bool	move_chk(t_map_chk *info)
{
	if(info->map[info->p_y - 1][info->p_x] == '1' && info->map[info->p_y + 1][info->p_x] == '1'
		&& info->map[info->p_y][info->p_x - 1] == '1' && info->map[info->p_y][info->p_x + 1] == '1')
		{
			printf("No movement area for player\n");
			return(false);
		}
	return(true);
}

bool    map_parse(t_map_chk *info)
{
	int i = 0;
	int j = 0;

	while(info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if(!is_valid_char(info->map[i][j]))
			{
				printf("Invalid char in map\n");
				return(false);
			}
			j++;
		}
		i++;
	}
	if(!player_chk(info))
		return(false);
	if(!wall_check(info) || !move_chk(info))
		return(false);
	return(true);
}