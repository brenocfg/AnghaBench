#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widget ;
struct TYPE_6__ {int /*<<< orphan*/  get_desired_width; int /*<<< orphan*/  get_desired_height; int /*<<< orphan*/  resize; int /*<<< orphan*/  free; int /*<<< orphan*/  draw; } ;
struct TYPE_7__ {int size; void* xalign; void* yalign; int /*<<< orphan*/  icon_fetch_id; TYPE_1__ widget; } ;
typedef  TYPE_2__ icon ;
typedef  int /*<<< orphan*/  RofiDistance ;

/* Variables and functions */
 void* MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (double,void*) ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_VERTICAL ; 
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  WIDGET_TYPE_UNKNOWN ; 
 int distance_get_pixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* g_malloc0 (int) ; 
 int /*<<< orphan*/  icon_draw ; 
 int /*<<< orphan*/  icon_free ; 
 int /*<<< orphan*/  icon_get_desired_height ; 
 int /*<<< orphan*/  icon_get_desired_width ; 
 int /*<<< orphan*/  icon_resize ; 
 int /*<<< orphan*/  rofi_icon_fetcher_query (char const*,int) ; 
 int /*<<< orphan*/  rofi_theme_get_distance (int /*<<< orphan*/ ,char*,int) ; 
 void* rofi_theme_get_double (int /*<<< orphan*/ ,char*,double) ; 
 char* rofi_theme_get_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widget_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

icon * icon_create ( widget *parent, const char *name )
{
    icon *b = g_malloc0 ( sizeof ( icon ) );

    b->size = 16;
    // Initialize widget.
    widget_init ( WIDGET ( b ), parent, WIDGET_TYPE_UNKNOWN, name );
    b->widget.draw               = icon_draw;
    b->widget.free               = icon_free;
    b->widget.resize             = icon_resize;
    b->widget.get_desired_height = icon_get_desired_height;
    b->widget.get_desired_width  = icon_get_desired_width;

    RofiDistance d = rofi_theme_get_distance ( WIDGET (b), "size" , b->size );
    b->size = distance_get_pixel ( d, ROFI_ORIENTATION_VERTICAL );

    const char * filename = rofi_theme_get_string ( WIDGET ( b ), "filename", NULL );
    if ( filename ) {
        b->icon_fetch_id = rofi_icon_fetcher_query ( filename, b->size );
    }
    b->yalign = rofi_theme_get_double ( WIDGET ( b ), "vertical-align", 0.5 );
    b->yalign = MAX ( 0, MIN ( 1.0, b->yalign ) );
    b->xalign = rofi_theme_get_double ( WIDGET ( b ), "horizontal-align", 0.5 );
    b->xalign = MAX ( 0, MIN ( 1.0, b->xalign ) );

    return b;
}