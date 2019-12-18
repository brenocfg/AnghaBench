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
 scalar_t__ PANGO_SCALE ; 
 double char_height ; 
 int /*<<< orphan*/  p_metrics ; 
 int pango_font_metrics_get_ascent (int /*<<< orphan*/ ) ; 
 int pango_font_metrics_get_descent (int /*<<< orphan*/ ) ; 

double textbox_get_estimated_char_height ( void )
{
    if ( char_height < 0 ) {
        int height = pango_font_metrics_get_ascent ( p_metrics ) + pango_font_metrics_get_descent ( p_metrics );
        char_height = ( height ) / (double) PANGO_SCALE;
    }
    return char_height;
}