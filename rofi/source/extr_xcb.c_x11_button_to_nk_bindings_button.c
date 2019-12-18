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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  NkBindingsMouseButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NK_BINDINGS_MOUSE_BUTTON_BACK ; 
 int /*<<< orphan*/  NK_BINDINGS_MOUSE_BUTTON_EXTRA ; 
 int /*<<< orphan*/  NK_BINDINGS_MOUSE_BUTTON_FORWARD ; 
 int /*<<< orphan*/  NK_BINDINGS_MOUSE_BUTTON_MIDDLE ; 
 int /*<<< orphan*/  NK_BINDINGS_MOUSE_BUTTON_PRIMARY ; 
 int /*<<< orphan*/  NK_BINDINGS_MOUSE_BUTTON_SECONDARY ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static gboolean x11_button_to_nk_bindings_button ( guint32 x11_button, NkBindingsMouseButton *button )
{
    switch ( x11_button )
    {
    case 1:
        *button = NK_BINDINGS_MOUSE_BUTTON_PRIMARY;
        break;
    case 3:
        *button = NK_BINDINGS_MOUSE_BUTTON_SECONDARY;
        break;
    case 2:
        *button = NK_BINDINGS_MOUSE_BUTTON_MIDDLE;
        break;
    case 8:
        *button = NK_BINDINGS_MOUSE_BUTTON_BACK;
        break;
    case 9:
        *button = NK_BINDINGS_MOUSE_BUTTON_FORWARD;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        return FALSE;
    default:
        *button = NK_BINDINGS_MOUSE_BUTTON_EXTRA + x11_button;
    }
    return TRUE;
}