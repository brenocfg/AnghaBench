#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_atom_t ;
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 size_t _MOTIF_WM_HINTS ; 
 int /*<<< orphan*/ * netatoms ; 
 TYPE_1__* xcb ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct MotifWMHints*) ; 

void x11_disable_decoration ( xcb_window_t window )
{
    // Flag used to indicate we are setting the decoration type.
    const uint32_t MWM_HINTS_DECORATIONS = ( 1 << 1 );
    // Motif property data structure
    struct MotifWMHints
    {
        uint32_t flags;
        uint32_t functions;
        uint32_t decorations;
        int32_t  inputMode;
        uint32_t state;
    };

    struct MotifWMHints hints;
    hints.flags       = MWM_HINTS_DECORATIONS;
    hints.decorations = 0;
    hints.functions   = 0;
    hints.inputMode   = 0;
    hints.state       = 0;

    xcb_atom_t ha = netatoms[_MOTIF_WM_HINTS];
    xcb_change_property ( xcb->connection, XCB_PROP_MODE_REPLACE, window, ha, ha, 32, 5, &hints );
}