#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct skyscraper {int color; int xoff; int width; int height; int windows; } ;
struct TYPE_4__ {int width; int height; } ;
typedef  TYPE_1__ lwCanvas ;

/* Variables and functions */
 int /*<<< orphan*/  generateSkyscraper (TYPE_1__*,struct skyscraper*) ; 
 int rand () ; 

void generateSkyline(lwCanvas *canvas) {
    struct skyscraper si;

    /* First draw the background skyscraper without windows, using the
     * two different grays. We use two passes to make sure that the lighter
     * ones are always in the background. */
    for (int color = 2; color >= 1; color--) {
        si.color = color;
        for (int offset = -10; offset < canvas->width;) {
            offset += rand() % 8;
            si.xoff = offset;
            si.width = 10 + rand()%9;
            if (color == 2)
                si.height = canvas->height/2 + rand()%canvas->height/2;
            else
                si.height = canvas->height/2 + rand()%canvas->height/3;
            si.windows = 0;
            generateSkyscraper(canvas, &si);
            if (color == 2)
                offset += si.width/2;
            else
                offset += si.width+1;
        }
    }

    /* Now draw the foreground skyscraper with the windows. */
    si.color = 0;
    for (int offset = -10; offset < canvas->width;) {
        offset += rand() % 8;
        si.xoff = offset;
        si.width = 5 + rand()%14;
        if (si.width % 4) si.width += (si.width % 3);
        si.height = canvas->height/3 + rand()%canvas->height/2;
        si.windows = 1;
        generateSkyscraper(canvas, &si);
        offset += si.width+5;
    }
}