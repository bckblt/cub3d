# cub3d

Wolfenstein 3D'den ilham alınan, raycasting ile oluşturulmuş 3D FPS motoru — 42 İstanbul projesi.

## Nasıl Çalışır?

2D harita verisi, **DDA raycasting** algoritmasıyla her sütun için duvara olan mesafe hesaplanarak gerçek zamanlı 3D perspektife dönüştürülür. Her duvar yönüne (N/S/E/W) farklı texture uygulanır.

## Kontroller

- `W A S D` → hareket
- `←` `→` → kamera döndürme
- `ESC` → çıkış

## Kullanım

```bash
make
./cub3d maps/map.cub
```

## Özellikler

- Raycasting tabanlı 3D render
- Yön bazlı duvar texture'ları (N/S/E/W)
- Minimap
- `.cub` format harita ayrıştırma ve doğrulama

## Teknolojiler

`MiniLibX` · `Raycasting` · `DDA` · `libft` · `gnl` · C

---

**bakarabu** — 42 İstanbul
