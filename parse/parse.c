#include "cub3d.h"

bool	file_structure(t_map_chk *info)
{
	int i = 0;
	while(i < info->map_start - 1)
	{
		if(find_elements("NO", info->full_file[i], '\0') || find_elements("WE", info->full_file[i], '\0')
			|| find_elements("EA", info->full_file[i], '\0') || find_elements("SO", info->full_file[i], '\0')
			|| find_elements(NULL, info->full_file[i], 'F') || find_elements(NULL, info->full_file[i], 'C')
			|| info->full_file[i][0] == '\n')
			i++;
		else
			return(false);
	}
	return(true);
}

bool	same_direc(t_map_chk *info)
{
	int i = 0;
	int n_c = 0;
	int w_c = 0;
	int s_c = 0;
	int e_c = 0;
	while(i < info->map_start - 1)
	{
		if(find_elements("NO", info->full_file[i], '\0'))
			n_c++;
		if(find_elements("SO", info->full_file[i], '\0'))
			s_c++;
		if(find_elements("WE", info->full_file[i], '\0'))
			w_c++;
		if(find_elements("EA", info->full_file[i], '\0'))
			e_c++;
		i++;
	}
	if(n_c != 1 || w_c != 1 || e_c != 1 || s_c != 1)
		return(false);
	return(true);
}

bool	check_file(char *file_name, char *to_find)
{
	char *tmp;

	tmp = ft_strtrim(file_name, to_find);
	if(!is_valid_file(tmp))
	{
		free(tmp);
		printf("textures not found\n");
		return(false);
	}
	free(tmp);
	return(true);
}

bool	file_path_chk(t_map_chk *info)
{	
	if(check_file(info->NT, "NO \n") == 0)
		return(false);
	if(check_file(info->ST, "SO \n") == 0)
		return(false);
	if(check_file(info->WT, "WE \n") == 0)
		return(false);
	if(check_file(info->ET, "EA \n") == 0)
		return(false);

	info->NT = ft_strtrim(info->NT, "NO \n");
	info->ET = ft_strtrim(info->ET, "EA \n");
	info->WT = ft_strtrim(info->WT, "WE \n");
	info->ST = ft_strtrim(info->ST, "SO \n");
	return(true);
}

int	get_rgb(char **str_rgb)
{
	int a[3];
	int i = 0;
	int color;

	while(i < 3)
	{
		a[i] = ft_atoi(str_rgb[i]);
		i++;
	}
	color = (a[0] << 16) | (a[1] << 8) | a[2];
	return(color);
}

bool	valid_color(t_map_chk *info, char *color, char *to_find, char key)
{
	char *tmp;
	char **tmp2;
	int i = 0;

	tmp = ft_strtrim(color, to_find);
	tmp2 = ft_split(tmp, ',');
	while (tmp2[i])
		i++;
	if(i >= 4 || !rgb_chk(tmp2) || !comma_chk(tmp) || !tmp2[2])
	{
		free(tmp);
		free_dp(tmp2);
		return(false);
	}
	if(key == 'F')
	info->F_C = get_rgb(tmp2);
	if(key == 'C')
	info->C_C = get_rgb(tmp2);
	free_dp(tmp2);
	free(tmp);
	return(true);
}

bool	colour_format(t_map_chk *info)
{
	if(!valid_color(info, info->F, "F \n", 'F'))
	{
		printf("Colour format must be RGB\n");
		return(false);
	}
	if(!valid_color(info, info->C, "C \n", 'C'))
	{
		printf("Colour format must be RGB\n");
		return(false);
	}
	return(true);
}

t_map_chk    *parse(char *file)
{
	t_map_chk *info;
	info = malloc(sizeof(t_map_chk));
	if(!check_file_name(file))
	{
		free(info);
		printf("File format must be \".cub\"\n");
		return NULL;
	}
	if(!is_valid_file(file))
	{
		printf("File not found\n");
		return NULL;
	}
	info = get_file(file, info);
	if(!get_textures_and_map(info) || !same_direc(info))
	{
		free_dp(info->full_file);
		free(info);
		printf("Each element can only be defined once\n");
		return NULL;
	}
	if(info->map[0] == NULL)
	{
		free_dp(info->full_file);
		free_dp(info->map);
		free(info);
		printf("Map not found\n");
		return NULL;
	}
	if(!file_structure(info))
	{
		printf("Wrong file format\n");
		return NULL;
	}
	if(!file_path_chk(info))
	{
		free_dp(info->full_file);
		free_dp(info->map);
		free(info);
		return NULL;
	}
	if(!colour_format(info) || !map_parse(info))
	{
		free_dp(info->full_file);
		free_dp(info->map);
		free(info->ET);
		free(info->WT);
		free(info->ST);
		free(info->NT);
		free(info);
		return NULL;
	}
	return (info);
}