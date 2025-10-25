#include "cub3d.h"

bool	comma_chk(char *str)
{
	int i = 0;
	if(str[i] == ',' || str[ft_strlen(str) - 1] == ',')
		return(false);
	while(str[i])
	{
		if(str[i] == ',' && str[i + 1] == ',')
			return(false);
		i++;
	}
	return(true);
}

bool	rgb_chk(char **colour)
{
	int i = 0;
	int j = 0;

	while(colour[i])
	{
		j = 0;
		while(colour[i][j])
		{
			if(!((colour[i][j] <= '9' && colour[i][j] >= '0') || colour[i][j] >= ' '))
				return(false);
			j++;
		}
		i++;
	}
	i = 0;
	while(colour[i])
	{
		j = ft_atoi(colour[i]);
		if(j < 0 || j > 255)
			return(false);
		i++;
	}
	return(true);
}

bool	is_valid_file(char *file)
{
	if(access(file, F_OK) == 0)
		return (true);
	else
		return(false);
}

bool check_file_name(char *file)
{
	int i = 0;
	char *tmp;

	if(file[0] == '.')
		return(false);
	while(file[i])
	{
		if(file[i] != '.')
			i++;
		else
		{
			if(file[i + 1] != 'c' || file[i + 2] != 'u' || file[i + 3] != 'b' || file[i + 4] != '\0')
				return(false);
			else
				return(true);
		}
	}
	tmp = ft_strchr(file, '.');
	if(tmp == NULL)
		return(false);
	return(true);
}

void	free_dp(char **str)
{
	int i = 0;
	if(!str)
		return ;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

bool	is_valid_char(char a)
{
	if(a != '0' && a != '1' && a != 'N' && a != 'W' && a != 'S'
		&& a != 'E' && a != '\n' && a != '\0' && a != ' ')
	{
		return(false);
	}
	return(true);
}

char	**map_copy(char **map)
{
	char **cp_map;
	int i = 0;

	while(map[i])
		i++;
	cp_map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(map[i])
	{ 
		cp_map[i] = ft_strdup(map[i]);
		i++;
	}
	cp_map[i] = NULL;
	return(cp_map);
}