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
typedef  int guint32 ;
typedef  int gint32 ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  NkBindingsScrollAxis ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NK_BINDINGS_SCROLL_AXIS_HORIZONTAL ; 
 int /*<<< orphan*/  NK_BINDINGS_SCROLL_AXIS_VERTICAL ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static gboolean x11_button_to_nk_bindings_scroll ( guint32 x11_button, NkBindingsScrollAxis *axis, gint32 *steps )
{
    *steps = 1;
    switch ( x11_button )
    {
    case 4:
        *steps = -1;
    /* fallthrough */
    case 5:
        *axis = NK_BINDINGS_SCROLL_AXIS_VERTICAL;
        break;
    case 6:
        *steps = -1;
    /* fallthrough */
    case 7:
        *axis = NK_BINDINGS_SCROLL_AXIS_HORIZONTAL;
        break;
    default:
        return FALSE;
    }
    return TRUE;
}