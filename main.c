#include "cub3d.h"

int main(int ac, char **av)
{
    t_map_chk *info;
    t_game *game;
    if(ac != 2)
    {
        printf("Please use this format : ./cub3D map.cub\n");
        exit(1);
    }
    info = parse(av[1]);
    if(!info)
        return(0);
    game = malloc(sizeof(t_game));
    ft_memset(game, 0, sizeof(t_game));
    game_engine(game, info);
    return(0);
}