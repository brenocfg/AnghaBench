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
typedef  int /*<<< orphan*/  lwCanvas ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  lwDrawPixel (int /*<<< orphan*/ *,int,int,int) ; 

void lwDrawLine(lwCanvas *canvas, int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx-dy, e2;

    while(1) {
        lwDrawPixel(canvas,x1,y1,color);
        if (x1 == x2 && y1 == y2) break;
        e2 = err*2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}