#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widget ;
struct TYPE_5__ {int h; } ;
struct TYPE_6__ {int flags; scalar_t__ changed; TYPE_1__ widget; } ;
typedef  TYPE_2__ textbox ;

/* Variables and functions */
 int TB_AUTOHEIGHT ; 
 int /*<<< orphan*/  __textbox_update_pango_text (TYPE_2__*) ; 
 int textbox_get_height (TYPE_2__*) ; 

__attribute__((used)) static int textbox_get_desired_height ( widget *wid )
{
    textbox *tb = (textbox *) wid;
    if ( ( tb->flags & TB_AUTOHEIGHT ) == 0 ) {
        return tb->widget.h;
    }
    if ( tb->changed ) {
        __textbox_update_pango_text ( tb );
    }
    int height = textbox_get_height ( tb );
    return height;
}