#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ expand; int /*<<< orphan*/  enabled; } ;
typedef  TYPE_1__ widget ;
struct TYPE_12__ {scalar_t__ type; int /*<<< orphan*/  children; int /*<<< orphan*/  spacing; } ;
typedef  TYPE_2__ box ;
struct TYPE_13__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  RofiDistance ;
typedef  TYPE_3__ GList ;

/* Variables and functions */
 int MAX (scalar_t__,int) ; 
 scalar_t__ ROFI_ORIENTATION_HORIZONTAL ; 
 scalar_t__ TRUE ; 
 int distance_get_pixel (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* g_list_first (int /*<<< orphan*/ ) ; 
 TYPE_3__* g_list_next (TYPE_3__*) ; 
 int /*<<< orphan*/  rofi_theme_get_distance (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ widget_get_desired_width (TYPE_1__*) ; 
 scalar_t__ widget_padding_get_padding_width (TYPE_1__*) ; 

__attribute__((used)) static int box_get_desired_width  ( widget *wid )
{
    box *b      = (box *) wid;
    int spacing = distance_get_pixel ( b->spacing, b->type );
    int width   = 0;

    // Allow user to override.
    RofiDistance w = rofi_theme_get_distance ( wid, "width", 0 );
    width = distance_get_pixel ( w, ROFI_ORIENTATION_HORIZONTAL );
    if ( width > 0 ) {
        return width;
    }

    if ( b->type == ROFI_ORIENTATION_HORIZONTAL ) {
        int active_widgets = 0;
        for ( GList *iter = g_list_first ( b->children ); iter != NULL; iter = g_list_next ( iter ) ) {
            widget * child = (widget *) iter->data;
            if ( !child->enabled ) {
                continue;
            }
            active_widgets++;
            if ( child->expand == TRUE ) {
                width += widget_get_desired_width ( child );
                continue;
            }
            width += widget_get_desired_width ( child );
        }
        if ( active_widgets > 0 ) {
            width += ( active_widgets - 1 ) * spacing;
        }
    }
    else {
        for ( GList *iter = g_list_first ( b->children ); iter != NULL; iter = g_list_next ( iter ) ) {
            widget * child = (widget *) iter->data;
            if ( !child->enabled ) {
                continue;
            }
            width = MAX ( widget_get_desired_width ( child ), width );
        }
    }
    width += widget_padding_get_padding_width ( wid );
    return width;
}