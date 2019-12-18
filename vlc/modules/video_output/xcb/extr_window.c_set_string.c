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
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  xcb_atom_t ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline
void set_string (xcb_connection_t *conn, xcb_window_t window,
                 xcb_atom_t type, xcb_atom_t atom, const char *str)
{
    xcb_change_property (conn, XCB_PROP_MODE_REPLACE, window, atom, type,
                         /* format */ 8, strlen (str), str);
}