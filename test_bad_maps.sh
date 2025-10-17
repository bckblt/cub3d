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
echo -e "${YELLOW}=== Cub3D Bad Maps Test Suite ===${NC}\n"

# Önce projeyi derle
echo "Projeyi derleme..."
make re > /dev/null 2>&1

# maps/bad klasöründeki her dosya için test
for map in maps/bad/*.cub maps/bad/filetype_* maps/bad/empty.cub; do
    TOTAL=$((TOTAL + 1))
    mapname=$(basename "$map")
    
    echo -n "Testing $mapname: "
    
    # Programı çalıştır
    ./cub3d "$map" > /dev/null 2>&1
    exit_code=$?

    # Hata kodu 0 değilse (hata varsa) başarılı
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}FAIL${NC}"
        echo "Program hata vermedi ama vermeliydi!"
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