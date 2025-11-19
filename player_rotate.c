#include "cub3d.h"

void move_forward(t_game *game)
{
    double moveSpeed = 0.13;
    double newX = game->player->x + game->player->dirx * moveSpeed;
    double newY = game->player->y + game->player->diry * moveSpeed;
    
    // Çarpışma kontrolü
    if (game->info->map[(int)game->player->y][(int)newX] != '1')
        game->player->x = newX;
    if (game->info->map[(int)newY][(int)game->player->x] != '1')
        game->player->y = newY;
}

void move_backward(t_game *game)
{
    double moveSpeed = 0.1;
    double newX = game->player->x - game->player->dirx * moveSpeed;
    double newY = game->player->y - game->player->diry * moveSpeed;
    
    if (game->info->map[(int)game->player->y][(int)newX] != '1')
        game->player->x = newX;
    if (game->info->map[(int)newY][(int)game->player->x] != '1')
        game->player->y = newY;
}

void rotate_left(t_game *game)
{
    double rotSpeed = 0.05;
    double oldDirX = game->player->dirx;
    double oldPlaneX = game->planeX;
    
    // Yön vektörünü döndür
    game->player->dirx = game->player->dirx * cos(-rotSpeed) - game->player->diry * sin(-rotSpeed);
    game->player->diry = oldDirX * sin(-rotSpeed) + game->player->diry * cos(-rotSpeed);
    
    // Kamera düzlemini döndür
    game->planeX = game->planeX * cos(-rotSpeed) - game->planeY * sin(-rotSpeed);
    game->planeY = oldPlaneX * sin(-rotSpeed) + game->planeY * cos(-rotSpeed);
}

void rotate_right(t_game *game)
{
    double rotSpeed = 0.05;
    double oldDirX = game->player->dirx;
    double oldPlaneX = game->planeX;

    game->player->dirx = oldDirX * cos(rotSpeed) - game->player->diry * sin(rotSpeed);
    game->player->diry = oldDirX * sin(rotSpeed) + game->player->diry * cos(rotSpeed);    
    game->planeX = game->planeX * cos(rotSpeed) - game->planeY * sin(rotSpeed);
    game->planeY = oldPlaneX * sin(rotSpeed) + game->planeY * cos(rotSpeed);
}

void strafe_left(t_game *game)
{
    double moveSpeed = 0.05;
    double newX = game->player->x - game->planeX * moveSpeed;
    double newY = game->player->y - game->planeY * moveSpeed;
    
    if (game->info->map[(int)game->player->y][(int)newX] != '1')
        game->player->x = newX;
    if (game->info->map[(int)newY][(int)game->player->x] != '1')
        game->player->y = newY;
}

void strafe_right(t_game *game)
{
    double moveSpeed = 0.05;
    double newX = game->player->x + game->planeX * moveSpeed;
    double newY = game->player->y + game->planeY * moveSpeed;
    
    if (game->info->map[(int)game->player->y][(int)newX] != '1')
        game->player->x = newX;
    if (game->info->map[(int)newY][(int)game->player->x] != '1')
        game->player->y = newY;
}