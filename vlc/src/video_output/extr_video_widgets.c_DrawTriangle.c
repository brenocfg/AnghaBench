#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_2__* p_picture; } ;
typedef  TYPE_3__ subpicture_region_t ;
struct TYPE_7__ {TYPE_1__* p; } ;
struct TYPE_6__ {int i_pitch; int /*<<< orphan*/ * p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DrawRect (TYPE_3__*,int,int /*<<< orphan*/ ,int const,int,int,int) ; 
 int STYLE_FILLED ; 
 int __MAX (int,int) ; 
 int __MIN (int,int) ; 

__attribute__((used)) static void DrawTriangle(subpicture_region_t *r, int fill, uint8_t color,
                         int x1, int y1, int x2, int y2)
{
    uint8_t *p    = r->p_picture->p->p_pixels;
    int     pitch = r->p_picture->p->i_pitch;
    const int mid = y1 + (y2 - y1) / 2;
    const bool b_swap = (x1 > x2);

    for (int y = y1; y <= mid; y++) {
        const int h = y - y1;
        if (fill == STYLE_FILLED) {
            const int w = b_swap ? __MAX(x1 - h, x2) : __MIN(x1 + h, x2);
            DrawRect(r, STYLE_FILLED, color,
                     (b_swap) ? w : x1, y, (b_swap) ? x1 : w, y);
            DrawRect(r, STYLE_FILLED, color,
                     (b_swap) ? w : x1, y2 - h, (b_swap) ? x1 : w, y2 - h);
        } else {
            p[x1 +                     pitch * y       ] = color;
            p[x1 + (b_swap ? -h : h) + pitch * y       ] = color;
            p[x1 +                     pitch * (y2 - h)] = color;
            p[x1 + (b_swap ? -h : h) + pitch * (y2 - h)] = color;
        }
    }
}