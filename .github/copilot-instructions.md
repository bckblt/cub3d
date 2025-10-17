# Cub3D - Raycasting Oyun Motoru AI Kılavuzu

Bu belge, Cub3D projesinde AI asistanların hızlı ve etkili bir şekilde çalışabilmesi için temel bilgileri içerir.

## Proje Yapısı

Cub3D, Wolfenstein 3D tarzı bir raycasting oyun motorudur. Temel bileşenleri:

### Çekirdek Bileşenler
- `cub3d.h`: Temel veri yapıları ve fonksiyon prototiplerini içerir
- `engine.c`: Ana oyun motoru mantığı
- `render_frame.c`: Görüntü oluşturma ve rendering işlemleri
- `player_rotate.c`: Oyuncu hareket ve rotasyon kontrolü

### Alt Sistemler
- `/parse`: Harita ve konfigürasyon dosyası işleme
- `/gnl`: Dosya okuma yardımcı fonksiyonları
- `/libft`: Özel C yardımcı fonksiyon kütüphanesi
- `/minilibx-linux`: Grafik kütüphanesi

## Temel İş Akışları

### Derleme
```bash
make        # Normal derleme
make re     # Temizle ve yeniden derle
make clean  # Obje dosyalarını temizle
make fclean # Tüm oluşturulan dosyaları temizle
```

### Harita Formatı
- `.cub` uzantılı dosyalar
- Harita sembolleri:
  - `0`: Boş alan
  - `1`: Duvar
  - `N/S/E/W`: Oyuncu başlangıç pozisyonu ve yönü

### Test Senaryoları
- `/maps/good`: Geçerli test haritaları
- `/maps/bad`: Hata senaryoları için test haritaları

## Önemli Kalıplar

### Veri Yapıları
- `t_game`: Ana oyun durumu
- `t_player`: Oyuncu pozisyonu ve yönü
- `t_ray`: Raycasting hesaplamaları
- `t_map_chk`: Harita doğrulama ve parsing

### Hata İşleme
- Harita doğrulama hataları `parse/parse_utils.c` içinde işlenir
- Bellek yönetimi için libft fonksiyonları kullanılır

## Entegrasyon Noktaları
- MinilibX: Pencere yönetimi ve grafik işlemleri için
- libft: Temel C fonksiyonları için özelleştirilmiş kütüphane

## İyi Pratikler
- Yeni harita özelliklerini eklerken `/maps/bad` altında hata senaryoları ekleyin
- Bellek sızıntılarını önlemek için tüm malloc/free çiftlerini takip edin
- Raycasting hesaplamalarında performans için optimizasyon yapın

## Önemli Dosyalar
- `cub3d.h`: Tüm yapıları ve prototipleri içerir
- `engine.c`: Ana oyun döngüsü ve mantığı
- `parse/map_parse.c`: Harita doğrulama kuralları
- `render_frame.c`: Raycasting ve rendering implementasyonu