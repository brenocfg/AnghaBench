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
struct TYPE_3__ {int width; int height; int* pixels; } ;
typedef  TYPE_1__ lwCanvas ;

/* Variables and functions */

void lwDrawPixel(lwCanvas *canvas, int x, int y, int color) {
    if (x < 0 || x >= canvas->width ||
        y < 0 || y >= canvas->height) return;
    canvas->pixels[x+y*canvas->width] = color;
}