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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  XA_WM_HINTS ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int const*) ; 

__attribute__((used)) static inline
void set_wm_hints (xcb_connection_t *conn, xcb_window_t window)
{
    static const uint32_t wm_hints[8] = {
        3, /* flags: Input, Initial state */
        1, /* input: True */
        1, /* initial state: Normal */
        0, 0, 0, 0, 0, /* Icon */
    };
    xcb_change_property (conn, XCB_PROP_MODE_REPLACE, window, XA_WM_HINTS,
                         XA_WM_HINTS, 32, 8, wm_hints);
}