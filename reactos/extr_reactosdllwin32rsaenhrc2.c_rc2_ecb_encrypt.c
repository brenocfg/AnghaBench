#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* xkey; } ;
typedef  TYPE_1__ rc2_key ;

/* Variables and functions */

void rc2_ecb_encrypt( const unsigned char *plain,
                            unsigned char *cipher,
                            rc2_key *rc2)
{
    unsigned *xkey;
    unsigned x76, x54, x32, x10, i;

    xkey = rc2->xkey;

    x76 = ((unsigned)plain[7] << 8) + (unsigned)plain[6];
    x54 = ((unsigned)plain[5] << 8) + (unsigned)plain[4];
    x32 = ((unsigned)plain[3] << 8) + (unsigned)plain[2];
    x10 = ((unsigned)plain[1] << 8) + (unsigned)plain[0];

    for (i = 0; i < 16; i++) {
        x10 = (x10 + (x32 & ~x76) + (x54 & x76) + xkey[4*i+0]) & 0xFFFF;
        x10 = ((x10 << 1) | (x10 >> 15));

        x32 = (x32 + (x54 & ~x10) + (x76 & x10) + xkey[4*i+1]) & 0xFFFF;
        x32 = ((x32 << 2) | (x32 >> 14));

        x54 = (x54 + (x76 & ~x32) + (x10 & x32) + xkey[4*i+2]) & 0xFFFF;
        x54 = ((x54 << 3) | (x54 >> 13));

        x76 = (x76 + (x10 & ~x54) + (x32 & x54) + xkey[4*i+3]) & 0xFFFF;
        x76 = ((x76 << 5) | (x76 >> 11));

        if (i == 4 || i == 10) {
            x10 = (x10 + xkey[x76 & 63]) & 0xFFFF;
            x32 = (x32 + xkey[x10 & 63]) & 0xFFFF;
            x54 = (x54 + xkey[x32 & 63]) & 0xFFFF;
            x76 = (x76 + xkey[x54 & 63]) & 0xFFFF;
        }
    }

    cipher[0] = (unsigned char)x10;
    cipher[1] = (unsigned char)(x10 >> 8);
    cipher[2] = (unsigned char)x32;
    cipher[3] = (unsigned char)(x32 >> 8);
    cipher[4] = (unsigned char)x54;
    cipher[5] = (unsigned char)(x54 >> 8);
    cipher[6] = (unsigned char)x76;
    cipher[7] = (unsigned char)(x76 >> 8);
}