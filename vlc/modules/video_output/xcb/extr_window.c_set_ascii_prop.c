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
 int /*<<< orphan*/  XA_STRING ; 
 int /*<<< orphan*/  set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline
void set_ascii_prop (xcb_connection_t *conn, xcb_window_t window,
                     xcb_atom_t atom, const char *value)
{
    set_string (conn, window, XA_STRING, atom, value);
}