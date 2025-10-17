#include "cub3d.h"

void init_player(t_game *game)
{
    int x = game->info->p_x;
    int y = game->info->p_y;
    char **map;
    map = game->info->map;
    // Haritada oyuncu pozisyonunu bul (N, S, E, W)
    if (map[y][x] == 'N' || map[y][x] == 'S' || 
        map[y][x] == 'E' || map[y][x] == 'W')
    {
        game->player->x = x + 0.5;  // Grid ortasına koy
        game->player->y = y + 0.5;
        
        // Başlangıç yönünü ayarla
        if (map[y][x] == 'N')
        {
            game->player->dirx = 0;
            game->player->diry = -1;
            game->planeX = 0.66;
            game->planeY = 0;
        }
        
        else if (map[y][x] == 'S')
        {
            game->player->dirx = 0;
            game->player->diry = 1;
            game->planeX = -0.66;
            game->planeY = 0;
        }
        else if (map[y][x] == 'E')
        {
            game->player->dirx = 1;
            game->player->diry = 0;
            game->planeX = 0;
            game->planeY = 0.66;
        }
        else if (map[y][x] == 'W')
        {
            game->player->dirx = -1;
            game->player->diry = 0;
            game->planeX = 0;
            game->planeY = -0.66;
        }
        map[y][x] = '0';  // Oyuncuyu haritadan sil
        return;
    }
}