#ifndef CUB_3D_H
#define CUB_3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./gnl/get_next_line.h"
#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"
#include <math.h>

typedef struct s_map_chk
{
    char **full_file;
    char **map;
    char *NT;
    char *ST;
    char *WT;
    char *ET;
    char *F;
    char *C;
    int map_start;
    int F_C;
    int C_C;
    int p_x;
    int p_y;
    //bunlara bilgisayarın desteklediği
    //tam ekran boyutu yazıldı oyun tam ekran olarak açılacak
    int max_x;
    int max_y;
}   t_map_chk;

typedef struct s_ray
{
    double rayDirX;     // Işının yön vektörü
    double rayDirY;
    double sideDistX;   // Sonraki grid çizgisine olan mesafe
    double sideDistY;
    double deltaDistX;  // Bir grid'den diğerine geçiş mesafesi
    double deltaDistY;
    double perpWallDist; // Duvara dik mesafe
    int mapX;           // Işının bulunduğu grid koordinatı
    int mapY;
    int stepX;          // Hangi yönde ilerliyoruz (-1 veya 1)
    int stepY;
    int hit;            // Duvara çarptı mı?
    int side;           // NS (0) veya EW (1) duvarı
}   t_ray;

typedef struct s_player
{
    //haritadaki koordinat
    double x;
    double y;
    //bakılan yön vektörü
    double  dirx;
    double  diry;

}   t_player;

typedef struct s_texture
{
    void *img;
    char *addr;
    int   width;
    int   height;
    int   bpp;
    int   line_length;
    int   endian;
}   t_texture;

typedef struct s_keys
{
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
}   t_keys;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *init;
    void *img;
    void *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    double planeX;
    double planeY;
    t_player *player;
    t_map_chk *info;

    t_texture tex_no;
    t_texture tex_so;
    t_texture tex_we;
    t_texture tex_ea;
    t_keys *keys;
}   t_game ;

t_map_chk    *parse(char *file);
bool check_file_name(char *file);
bool	is_valid_file(char *file);
void game_engine(t_game *game, t_map_chk *info);
bool check_file_name(char *file);
bool	is_valid_file(char *file);
t_map_chk	*get_file(char *file, t_map_chk *info);
void 	get_map(t_map_chk *info, int i);
bool	get_textures_and_map(t_map_chk *info);
void	free_dp(char **str);
bool	rgb_chk(char **colour);
bool	comma_chk(char *str);
bool    map_parse(t_map_chk *info);
bool	is_valid_char(char a);
char	**map_copy(char **map);
void strafe_right(t_game *game);
void strafe_left(t_game *game);
void rotate_right(t_game *game);
void rotate_left(t_game *game);
void move_backward(t_game *game);
void move_forward(t_game *game);
void load_textures(t_game *game);
void init_player(t_game *game);
void render_frame(t_game *game);
bool	find_elements(char *key, char *line, char a);




#endif