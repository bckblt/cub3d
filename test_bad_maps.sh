#!/bin/bash

# Renk kodları
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Sayaçlar
TOTAL=0
PASSED=0
FAILED=0

# Log klasörü
VALGRIND_DIR="valgrind_logs"
mkdir -p "$VALGRIND_DIR"

echo -e "${YELLOW}=== Cub3D Bad Maps Test Suite ===${NC}\n"

# Projeyi derle
echo "Projeyi derleme..."
make re > /dev/null 2>&1

# Test edilecek dosyalar
for map in maps/bad/*.cub maps/bad/filetype_* maps/bad/empty.cub; do
    TOTAL=$((TOTAL + 1))
    mapname=$(basename "$map")

    echo -n "Testing $mapname: "

    # Normal exit test
    ./cub3d "$map" > /dev/null 2>&1
    exit_code=$?

    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}FAIL${NC}"
        FAILED=$((FAILED + 1))
    fi

    # --- VALGRIND TAM ÇIKTI KAYDI ---
    VAL_FILE="${VALGRIND_DIR}/${mapname}.log"

    valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --errors-for-leak-kinds=all \
        --log-file="$VAL_FILE" \
        ./cub3d "$map" > /dev/null 2>&1
done

# Sonuç
echo -e "\n${YELLOW}=== Test Sonuçları ===${NC}"
echo "Toplam Test: $TOTAL"
echo -e "${GREEN}Başarılı (EXIT PASS): $PASSED${NC}"
echo -e "${RED}Başarısız (EXIT FAIL): $FAILED${NC}"

exit $FAILED
