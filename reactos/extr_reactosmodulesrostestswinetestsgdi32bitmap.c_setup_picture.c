#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static void setup_picture(char *picture, int bpp)
{
    int i;

    switch(bpp)
    {
        case 16:
        case 32:
            /*Set the first byte in each pixel to the index of that pixel.*/
            for (i = 0; i < 4; i++)
                picture[i * (bpp / 8)] = i;
            break;
        case 24:
            picture[0] = 0;
            picture[3] = 1;
            /*Each scanline in a bitmap must be a multiple of 4 bytes long.*/
            picture[8] = 2;
            picture[11] = 3;
            break;
    }
}