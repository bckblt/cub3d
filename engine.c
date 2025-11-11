#include "cub3d.h"

int exit_game(void *param)
{
    t_game *game = (t_game *)param;
    if (game)
    {
        if (game->img)
            mlx_destroy_image(game->init, game->img);
        if (game->win)
            mlx_destroy_window(game->init, game->win);
    }
    exit(0);
}

int key_press(int key, void *param)
{
    t_game *game = (t_game *)param;
    if (key == 53 || key == 65307)
        exit_game(game);
    else if (key == 13 || key == 126 || key == 119 || key == 65362)
        move_forward(game);
    else if (key == 1 || key == 125 || key == 115 || key == 65364)
        move_backward(game);
    else if (key == 0 || key == 97)  // A
        strafe_left(game);
    else if (key == 2 || key == 100)  // D
        strafe_right(game);
    else if (key == 123 || key == 65361)  // Left arrow
        rotate_left(game);
    else if (key == 124 || key == 65363)  // Right arrow
        rotate_right(game);

    
    render_frame(game);
    return (0);
}

int key_release(int keycode, t_game *game)
{
    (void)keycode;
    (void)game;
    return (0);
}

void game_engine(t_game *game, t_map_chk *info)
{
    game->info = info;
    game->init = mlx_init();
    if(!game->init)
    {
        printf("Error\nmlx_init_error\n");
        exit(1);
    }
    info->max_x = 1920;
    info->max_y = 1080;
    game->win = mlx_new_window((game->init), info->max_x, info->max_y, "cube3d");
    game->img =  mlx_new_image(game->init, info->max_x, info->max_y);
    game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);

    //down.. text.
    load_textures(game);
    game->player = malloc(sizeof(t_player));
    if(!game->player)
        exit(1);
    //player initialize
    init_player(game);

    //first frame initialize
    render_frame(game);

    mlx_hook(game->win, 17, 0, exit_game, game);
    mlx_hook(game->win, 2, 1L << 0, key_press, game);
    mlx_hook(game->win, 3, 1L << 1, key_release, game);
    mlx_loop(game->init);
}