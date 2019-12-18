#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widget ;
struct TYPE_4__ {int w; } ;
struct TYPE_5__ {int flags; TYPE_1__ widget; } ;
typedef  TYPE_2__ textbox ;

/* Variables and functions */
 unsigned int DOT_OFFSET ; 
 int TB_AUTOWIDTH ; 
 int TB_INDICATOR ; 
 int textbox_get_font_width (TYPE_2__*) ; 
 int widget_padding_get_padding_width (int /*<<< orphan*/ *) ; 

int textbox_get_width ( widget *wid )
{
    textbox *tb = (textbox *) wid;
    if ( tb->flags & TB_AUTOWIDTH ) {
        unsigned int offset = ( tb->flags & TB_INDICATOR ) ? DOT_OFFSET : 0;
        return textbox_get_font_width ( tb ) + widget_padding_get_padding_width ( wid ) + offset;
    }
    return tb->widget.w;
}