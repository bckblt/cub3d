#include "cub3d.h"

t_map_chk	*get_file(char *file, t_map_chk *info)
{
	char *line;
	int len = 0;
	int fd = open(file, O_RDONLY);

	line = get_next_line(fd);
	while(line)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	info->full_file = malloc(sizeof(char *) * (len + 1));
	len = 0;
	fd = open(file, O_RDONLY);

	line = get_next_line(fd);
	while(line)
	{
		info->full_file[len] = line;
		len++;
		line = get_next_line(fd);
	}
	info->full_file[len] = NULL;
	return(info);
}

void 	get_map(t_map_chk *info, int i)
{
	int temp;
	int len = 0;
	while(info->full_file[i] && (info->full_file[i][0] == '\n'))
		i++;
	temp = i;
	info->map_start = i;
	while(info->full_file[temp])
	{
		len++;
		temp++;
	}
	info->map = malloc(sizeof(char *) * (len + 1));
	if(!info->map)
		return ;
	len = 0;
	while(info->full_file[i])
	{
		info->map[len] = ft_strtrim(info->full_file[i], "\n");
		i++;
		len++;
	}
	info->map[len] = NULL;
}

bool	find_elements(char *key, char *line, char a)
{
	int i = 0;
	if(!key)
	{
		while(line[i])
		{
			if(line[i] == a)
				return(true);
			i++;
		}
	}
	else
	{
		while(line[i])
		{
			if(line[i] == key[0] && line[i + 1] == key[1])
				return(true);
			i++;
		}
	}
	return(false);
}

bool	get_textures_and_map(t_map_chk *info)
{
	int i = 0;
	int key = 0;
	int arg_c = 0;
	int j = 0;
	while(info->full_file[i])
	{
		if(find_elements("NO", info->full_file[i], '\0'))
		{
			info->NT = info->full_file[i];
			arg_c++;
		}
		if(find_elements("SO", info->full_file[i], '\0'))
		{
			info->ST = info->full_file[i];
			arg_c++;
		}
		if(find_elements("EA", info->full_file[i], '\0'))
		{
			info->ET = info->full_file[i];
			arg_c++;
		}
		if(find_elements("WE", info->full_file[i], '\0'))
		{
			info->WT = info->full_file[i];
			arg_c++;
		}
		if(find_elements(NULL, info->full_file[i], 'F'))
		{
			info->F = info->full_file[i];
			arg_c++;
		}
		if(find_elements(NULL, info->full_file[i], 'C'))
		{
			info->C = info->full_file[i];
			arg_c++;
		}
		if(arg_c == 6 && key == 0)
		{
			key = 1;
			j = i + 1;
		}
		i++;
	}
	if(arg_c != 6)
		return(false);
	get_map(info, j);
	return(true);
}
