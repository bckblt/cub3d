#include "cub3d.h"

static void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= game->info->max_x || y < 0 || y >= game->info->max_y)
        return;

    char *dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

static void draw_minimap_square(t_game *game, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < 10)
    {
        j = 0;
        while (j < 10)
        {
            my_mlx_pixel_put(game, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void render_minimap(t_game *game)
{
    int map_y = 0;
    int map_x;
    int i;
    int j;

    i = 0;
    j = 0;
    while (game->info->map[map_y])
    {
        map_x = 0;
        while (game->info->map[map_y][map_x])
        {
            int screen_x = map_x * 10;
            int screen_y = map_y * 10;
            if (game->info->map[map_y][map_x] == '1')
                draw_minimap_square(game, screen_x, screen_y, 0x808080);
            map_x++;
        }
        map_y++;
    }
    int p_screen_x = (int)(game->player->x * 10);
    int p_screen_y = (int)(game->player->y * 10);
    int p_size = 10 / 2;
    while (i < p_size)
    {
        j = 0;
        while (j < p_size)
        {
            my_mlx_pixel_put(game, p_screen_x + j - (p_size/2), p_screen_y + i - (p_size/2), 0xFF0000);
            j++;
        }
        i++;
    }
}