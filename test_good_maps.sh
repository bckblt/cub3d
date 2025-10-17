#!/bin/bash

# Renk kodları
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Test sayacı
TOTAL=0
PASSED=0
FAILED=0

# Başlık yazdır
echo -e "${YELLOW}=== Cub3D Good Maps Test Suite ===${NC}\n"

# Önce projeyi derle
echo "Projeyi derleme..."
make re > /dev/null 2>&1

# maps/good klasöründeki her dosya için test
for map in maps/good/*.cub; do
    TOTAL=$((TOTAL + 1))
    mapname=$(basename "$map")
    
    echo -n "Testing $mapname: "
    
    # Programı çalıştır ve ESC tuşuna basma simülasyonu yap
    ./cub3d "$map" >/dev/null 2>&1 &
    sleep 1
    pid=$!
    
    if ps -p $pid > /dev/null; then
        echo -e "${GREEN}PASS${NC} (Pencere başarıyla açıldı)"
        kill -9 $pid 2>/dev/null
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}FAIL${NC} (Program beklenmedik şekilde kapandı)"
        FAILED=$((FAILED + 1))
    fi

done

# Sonuçları yazdır
echo -e "\n${YELLOW}=== Test Sonuçları ===${NC}"
echo "Toplam Test: $TOTAL"
echo -e "${GREEN}Başarılı: $PASSED${NC}"
echo -e "${RED}Başarısız: $FAILED${NC}"

# Çıkış kodu olarak başarısız test sayısını döndür
exit $FAILED