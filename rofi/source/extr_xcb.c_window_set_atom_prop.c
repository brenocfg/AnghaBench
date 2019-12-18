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
struct TYPE_2__ {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_ATOM_ATOM ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 TYPE_1__* xcb ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

void window_set_atom_prop ( xcb_window_t w, xcb_atom_t prop, xcb_atom_t *atoms, int count )
{
    xcb_change_property ( xcb->connection, XCB_PROP_MODE_REPLACE, w, prop, XCB_ATOM_ATOM, 32, count, atoms );
}