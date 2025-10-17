#include "cub3d.h"


static void draw_textured_column(t_game *game, int x, int drawStart, int drawEnd, t_texture *tex, int texX, int side)
{
    if (!tex || !tex->addr || tex->width <= 0 || tex->height <= 0)
        return;
    int y = 0;
    char *dst;
    int screenH = game->info->max_y;

    // Ceiling
    while (y < drawStart)
    {
        dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
        *(unsigned int*)dst = (unsigned int)game->info->C_C;
        y++;
    }

    int lineHeight = drawEnd - drawStart + 1;
    double step = (double)tex->height / (double)lineHeight;
    double texPos = (drawStart - screenH / 2.0 + lineHeight / 2.0) * step;

    // Wall
    while (y <= drawEnd && y < screenH)
    {
        int texY = (int)texPos;
        if (texY < 0) texY = 0;
        if (texY >= tex->height) texY = tex->height - 1;
        texPos += step;

        char *src = tex->addr + (texY * tex->line_length + texX * (tex->bpp / 8));
        unsigned int color = *(unsigned int*)src;

        if (side == 1) // shade y-sides a bit darker
            color = (color >> 1) & 0x7F7F7F;

        dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
        y++;
    }

    // Floor
    while (y < screenH)
    {
        dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
        *(unsigned int*)dst = (unsigned int)game->info->F_C;
        y++;
    }
}

void calculate_wall_distance(t_ray *ray, t_player *player)
{
    // Duvara olan dik mesafeyi hesapla (fish-eye efektini önler)
    if (ray->side == 0)
        ray->perpWallDist = (ray->mapX - player->x + (1 - ray->stepX) / 2) / ray->rayDirX;
    else
        ray->perpWallDist = (ray->mapY - player->y + (1 - ray->stepY) / 2) / ray->rayDirY;
}

void perform_dda(t_ray *ray, t_map_chk *info)
{
    // DDA (Digital Differential Analyzer) algoritması
    // Harita yüksekliğini bir kere hesapla
    int mapH = 0;
    while (info->map[mapH])
        mapH++;

    while (ray->hit == 0)
    {
        // Bir sonraki grid çizgisine geç
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;  // Dikey duvar
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;  // Yatay duvar
        }

        // Harita sınır kontrolleri (dışına çıktıysa döngüyü sonlandır)
        if (ray->mapY < 0 || ray->mapY >= mapH)
        {
            ray->hit = 1;
            break;
        }
        int rowLen = (int)ft_strlen(info->map[ray->mapY]);
        if (ray->mapX < 0 || ray->mapX >= rowLen)
        {
            ray->hit = 1;
            break;
        }

        // Duvara çarptı mı kontrol et
        if (info->map[ray->mapY][ray->mapX] == '1')
            ray->hit = 1;
    }
}

void cast_single_ray(t_game *game, t_ray *ray, int x)
{
    double cameraX = 2 * x / (double)game->info->max_x - 1;  // -1 ile 1 arası
    
    // Işın yönünü hesapla
    ray->rayDirX = game->player->dirx + game->planeX * cameraX;
    ray->rayDirY = game->player->diry + game->planeY * cameraX;
    
    // Oyuncunun bulunduğu grid
    ray->mapX = (int)game->player->x;
    ray->mapY = (int)game->player->y;
    
    // Delta mesafeleri hesapla
    if (ray->rayDirX == 0)
        ray->deltaDistX = 1e30;
    else
        ray->deltaDistX = fabs(1 / ray->rayDirX);
    
    if (ray->rayDirY == 0)
        ray->deltaDistY = 1e30;
    else
        ray->deltaDistY = fabs(1 / ray->rayDirY);
    
    // Step ve ilk mesafeleri hesapla
    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (game->player->x - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - game->player->x) * ray->deltaDistX;
    }
    
    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (game->player->y - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - game->player->y) * ray->deltaDistY;
    }
    
    ray->hit = 0;
    
    // DDA algoritması ile duvar bul
    perform_dda(ray, game->info);
    
    // Duvara olan mesafeyi hesapla
    calculate_wall_distance(ray, game->player);
}

void render_frame(t_game *game)
{
    int x = 0;
    t_ray ray;
    
    while (x < game->info->max_x)
    {
        // Her x kolonu için bir ışın gönder
        cast_single_ray(game, &ray, x);
        
        // Duvar yüksekliğini hesapla
        int lineHeight = (int)(game->info->max_y / ray.perpWallDist);
        
        // Çizim başlangıç ve bitiş noktaları
        int drawStart = -lineHeight / 2 + game->info->max_y / 2;
        if (drawStart < 0)
            drawStart = 0;
        
        int drawEnd = lineHeight / 2 + game->info->max_y / 2;
        if (drawEnd >= game->info->max_y)
            drawEnd = game->info->max_y - 1;
        
        // Doku secimi
        t_texture *tex;
        if (ray.side == 1)
            tex = (ray.stepY > 0) ? &game->tex_so : &game->tex_no; // South / North
        else
            tex = (ray.stepX > 0) ? &game->tex_ea : &game->tex_we; // East / West

        // Texture X hesapla
        double wallX;
        if (ray.side == 0)
            wallX = game->player->y + ray.perpWallDist * ray.rayDirY;
        else
            wallX = game->player->x + ray.perpWallDist * ray.rayDirX;
        wallX -= floor(wallX);
        int texX = (int)(wallX * (double)tex->width);
        if (ray.side == 0 && ray.rayDirX > 0)
            texX = tex->width - texX - 1;
        if (ray.side == 1 && ray.rayDirY < 0)
            texX = tex->width - texX - 1;
        // Clamp texture coordinate to valid range
        if (texX < 0) texX = 0;
        if (texX >= tex->width) texX = tex->width - 1;

        // Dokusuz fonksiyon yerine dokulu cizim
        draw_textured_column(game, x, drawStart, drawEnd, tex, texX, ray.side);
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}