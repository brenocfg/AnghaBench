#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct skyscraper {int height; int xoff; int width; int color; scalar_t__ windows; } ;
struct TYPE_5__ {int height; } ;
typedef  TYPE_1__ lwCanvas ;

/* Variables and functions */
 int /*<<< orphan*/  lwDrawPixel (TYPE_1__*,int,int,int) ; 
 int lwGetPixel (TYPE_1__*,int,int) ; 
 int rand () ; 

void generateSkyscraper(lwCanvas *canvas, struct skyscraper *si) {
    int starty = canvas->height-1;
    int endy = starty - si->height + 1;
    for (int y = starty; y >= endy; y--) {
        for (int x = si->xoff; x < si->xoff+si->width; x++) {
            /* The roof is four pixels less wide. */
            if (y == endy && (x <= si->xoff+1 || x >= si->xoff+si->width-2))
                continue;
            int color = si->color;
            /* Alter the color if this is a place where we want to
             * draw a window. We check that we are in the inner part of the
             * skyscraper, so that windows are far from the borders. */
            if (si->windows &&
                x > si->xoff+1 &&
                x < si->xoff+si->width-2 &&
                y > endy+1 &&
                y < starty-1)
            {
                /* Calculate the x,y position relative to the start of
                 * the window area. */
                int relx = x - (si->xoff+1);
                int rely = y - (endy+1);

                /* Note that we want the windows to be two pixels wide
                 * but just one pixel tall, because terminal "pixels"
                 * (characters) are not square. */
                if (relx/2 % 2 && rely % 2) {
                    do {
                        color = 1 + rand() % 2;
                    } while (color == si->color);
                    /* Except we want adjacent pixels creating the same
                     * window to be the same color. */
                    if (relx % 2) color = lwGetPixel(canvas,x-1,y);
                }
            }
            lwDrawPixel(canvas,x,y,color);
        }
    }
}