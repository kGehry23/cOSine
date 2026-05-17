
#include "../bitmap.h"
#include "stdio.h"

int main(void)
{
    bitmap_t bmp;

    init_bitmap(&bmp);

    set_bit_high(&bmp, 0);
    printf("Bit state: %d\n", bit_state(&bmp, 0));

    set_bit_high(&bmp, 14);
    printf("bitmap: %p\n", bmp.bitmap);
    printf("Bit state: %d\n", bit_state(&bmp, 14));

    set_bit_low(&bmp, 0);
    printf("bitmap: %p\n", bmp.bitmap);

    set_bit_low(&bmp, 14);
    printf("bitmap: %p\n", bmp.bitmap);

    printf("Bit state: %d\n", bit_state(&bmp, 0));
}
