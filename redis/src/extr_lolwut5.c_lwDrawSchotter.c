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
 float RAND_MAX ; 
 int /*<<< orphan*/ * lwCreateCanvas (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwDrawSquare (int /*<<< orphan*/ *,int,int,float,float,int) ; 
 int rand () ; 

lwCanvas *lwDrawSchotter(int console_cols, int squares_per_row, int squares_per_col) {
    /* Calculate the canvas size. */
    int canvas_width = console_cols*2;
    int padding = canvas_width > 4 ? 2 : 0;
    float square_side = (float)(canvas_width-padding*2) / squares_per_row;
    int canvas_height = square_side * squares_per_col + padding*2;
    lwCanvas *canvas = lwCreateCanvas(canvas_width, canvas_height, 0);

    for (int y = 0; y < squares_per_col; y++) {
        for (int x = 0; x < squares_per_row; x++) {
            int sx = x * square_side + square_side/2 + padding;
            int sy = y * square_side + square_side/2 + padding;
            /* Rotate and translate randomly as we go down to lower
             * rows. */
            float angle = 0;
            if (y > 1) {
                float r1 = (float)rand() / RAND_MAX / squares_per_col * y;
                float r2 = (float)rand() / RAND_MAX / squares_per_col * y;
                float r3 = (float)rand() / RAND_MAX / squares_per_col * y;
                if (rand() % 2) r1 = -r1;
                if (rand() % 2) r2 = -r2;
                if (rand() % 2) r3 = -r3;
                angle = r1;
                sx += r2*square_side/3;
                sy += r3*square_side/3;
            }
            lwDrawSquare(canvas,sx,sy,square_side,angle,1);
        }
    }

    return canvas;
}