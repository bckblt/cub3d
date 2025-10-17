#include "cub3d.h"

static void load_texture(t_game *game, t_texture *tex, const char *path)
{
    tex->img = mlx_xpm_file_to_image(game->init, (char *)path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error\ntexture_load_failed: %s\n", path);
        exit(1);
    }
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length, &tex->endian);
    if (!tex->addr)
    {
        printf("Error\ntexture_data_addr_failed: %s\n", path);
        exit(1);
    }
}

void load_textures(t_game *game)
{
    load_texture(game, &game->tex_no, game->info->NT);
    load_texture(game, &game->tex_so, game->info->ST);
    load_texture(game, &game->tex_we, game->info->WT);
    load_texture(game, &game->tex_ea, game->info->ET);
}