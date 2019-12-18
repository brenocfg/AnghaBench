#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ parent; int /*<<< orphan*/  expand; scalar_t__ h; scalar_t__ w; } ;
typedef  TYPE_2__ widget ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_8__ {int w; int h; } ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  children; TYPE_1__ widget; } ;
typedef  TYPE_3__ box ;

/* Variables and functions */
 int MAX (int,scalar_t__) ; 
 scalar_t__ ROFI_ORIENTATION_VERTICAL ; 
 scalar_t__ WIDGET (TYPE_3__*) ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  g_list_append (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  rofi_theme_get_boolean (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ widget_padding_get_padding_height (scalar_t__) ; 
 scalar_t__ widget_padding_get_padding_width (scalar_t__) ; 
 int /*<<< orphan*/  widget_update (scalar_t__) ; 

void box_add ( box *box, widget *child, gboolean expand )
{
    if ( box == NULL ) {
        return;
    }
    // Make sure box is width/heigh enough.
    if ( box->type == ROFI_ORIENTATION_VERTICAL ) {
        int width = box->widget.w;
        width         = MAX ( width, child->w + widget_padding_get_padding_width ( WIDGET ( box ) ) );
        box->widget.w = width;
    }
    else {
        int height = box->widget.h;
        height        = MAX ( height, child->h + widget_padding_get_padding_height ( WIDGET ( box ) ) );
        box->widget.h = height;
    }
    child->expand = rofi_theme_get_boolean ( child, "expand", expand );
    g_assert ( child->parent == WIDGET ( box ) );
    box->children = g_list_append ( box->children, (void *) child );
    widget_update ( WIDGET ( box ) );
}