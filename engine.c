#include "cub3d.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int exit_game(void *param)
{
    t_game *game = (t_game *)param;

    if (!game)
        exit(0);
    if (game->img && game->init)
    {
        mlx_destroy_image(game->init, game->img);
        game->img = NULL;
        game->addr = NULL;
    }
    if (game->win && game->init)
    {
        mlx_destroy_window(game->init, game->win);
        game->win = NULL;
    }
    if (game->player)
    {
        free(game->player);
        game->player = NULL;
    }
    if (game->keys)
    {
        free(game->keys);
        game->keys = NULL;
    }
    exit(0);
}

int game_loop(void *param)
{
    t_game *g = (t_game *)param;
    if (!g)
        return (0);
    if (g->keys)
    {
        if (g->keys->w)
            move_forward(g);
        if (g->keys->s)
            move_backward(g);
        if (g->keys->a)
            strafe_left(g);
        if (g->keys->d)
            strafe_right(g);

        if (g->keys->left)
            rotate_left(g);
        if (g->keys->right)
            rotate_right(g);
    }
    render_frame(g);
    return (0);
}

int key_press(int key, void *param)
{
    t_game *g = (t_game *)param;

    if (!g)
        return (0);
    if (key == 53 || key == 65307) /* mac: 53, linux X11: 65307 (Esc) */
        exit_game(g);
    if (!g->keys)
        return (0);
    if (key == 13 || key == 126 || key == 119 || key == 65362) /* W / up */
        g->keys->w = 1;
    if (key == 1 || key == 125 || key == 115 || key == 65364)   /* S / down */
        g->keys->s = 1;
    if (key == 0 || key == 97)  /* A */
        g->keys->a = 1;
    if (key == 2 || key == 100) /* D */
        g->keys->d = 1;
    if (key == 123 || key == 65361) /* left arrow */
        g->keys->left = 1;
    if (key == 124 || key == 65363) /* right arrow */
        g->keys->right = 1;
    return (0);
}

int key_release(int key, void *param)
{
    t_game *g = (t_game *)param;

    if (!g || !g->keys)
        return (0);

    if (key == 13 || key == 126 || key == 119 || key == 65362) /* W / up */
        g->keys->w = 0;
    if (key == 1 || key == 125 || key == 115 || key == 65364)   /* S / down */
        g->keys->s = 0;
    if (key == 0 || key == 97)  /* A */
        g->keys->a = 0;
    if (key == 2 || key == 100) /* D */
        g->keys->d = 0;

    if (key == 123 || key == 65361)
        g->keys->left = 0;
    if (key == 124 || key == 65363)
        g->keys->right = 0;

    return (0);
}

void game_engine(t_game *game, t_map_chk *info)
{
    if (!game || !info)
    {
        fprintf(stderr, "Error: NULL game or info passed to game_engine\n");
        exit(1);
    }
    game->info = info;
    game->init = mlx_init();
    if (!game->init)
    {
        fprintf(stderr, "Error\nmlx_init_error\n");
        exit(1);
    }
    info->max_x = 1920;
    info->max_y = 1080;
    game->win = mlx_new_window(game->init, info->max_x, info->max_y, "cub3d");
    if (!game->win)
    {
        fprintf(stderr, "Error\nmlx_new_window failed\n");
        exit(1);
    }
    game->img = mlx_new_image(game->init, info->max_x, info->max_y);
    if (!game->img)
    {
        fprintf(stderr, "Error\nmlx_new_image failed\n");
        mlx_destroy_window(game->init, game->win);
        exit(1);
    }
    game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
    load_textures(game);
    game->player = (t_player *)malloc(sizeof(t_player));
    if (!game->player)
    {
        fprintf(stderr, "Error\nmalloc player failed\n");
        exit(1);
    }
    init_player(game);
    game->keys = (t_keys *)malloc(sizeof(t_keys));
    if (!game->keys)
    {
        fprintf(stderr, "Error\nmalloc keys failed\n");
        exit(1);
    }
    memset(game->keys, 0, sizeof(t_keys));
    render_frame(game);
    mlx_hook(game->win, 17, 0, exit_game, game);
    mlx_hook(game->win, 2, 1L << 0, key_press, game);
    mlx_hook(game->win, 3, 1L << 1, key_release, game);
    mlx_loop_hook(game->init, game_loop, game);
    mlx_loop(game->init);
}
