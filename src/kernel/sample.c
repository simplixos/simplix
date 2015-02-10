#include <bos/k/sample.h>

#ifdef __GNUC__
#include <stddef.h>
#endif

void sample_pi() {
    int r[2800 + 1];
    int i, k;
    int b, d;
    int c = 0;

    for (i = 0; i < 2800; i++) {
        r[i] = 2000;
    }

    for (k = 2800; k > 0; k -= 14) {
        d = 0;

        i = k;
        for (;;) {
            d += r[i] * 10000;
            b = 2 * i - 1;

            r[i] = d % b;
            d /= b;
            i--;
            if (i == 0) break;
            d *= i;
        }
        vga_write_dec((uint32_t)(c + d / 10000)); vga_write(" ");
        c = d % 10000;
    }
}
