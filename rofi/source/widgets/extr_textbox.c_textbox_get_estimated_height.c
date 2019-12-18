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
struct TYPE_4__ {int /*<<< orphan*/  metrics; } ;
typedef  TYPE_1__ textbox ;

/* Variables and functions */
 int PANGO_SCALE ; 
 int /*<<< orphan*/  WIDGET (TYPE_1__ const*) ; 
 int pango_font_metrics_get_ascent (int /*<<< orphan*/ ) ; 
 int pango_font_metrics_get_descent (int /*<<< orphan*/ ) ; 
 int widget_padding_get_padding_height (int /*<<< orphan*/ ) ; 

int textbox_get_estimated_height ( const textbox *tb, int eh )
{
    int height = pango_font_metrics_get_ascent ( tb->metrics ) + pango_font_metrics_get_descent ( tb->metrics );
    return ( eh * height ) / PANGO_SCALE + widget_padding_get_padding_height ( WIDGET ( tb ) );
}