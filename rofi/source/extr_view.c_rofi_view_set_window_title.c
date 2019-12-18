#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  main_window; } ;
struct TYPE_4__ {int /*<<< orphan*/  UTF8_STRING; int /*<<< orphan*/  _NET_WM_NAME; } ;
struct TYPE_5__ {int /*<<< orphan*/  connection; TYPE_1__ ewmh; } ;

/* Variables and functions */
 TYPE_3__ CacheState ; 
 int /*<<< orphan*/  XCB_ATOM_STRING ; 
 int /*<<< orphan*/  XCB_ATOM_WM_NAME ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 TYPE_2__* xcb ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*) ; 

void rofi_view_set_window_title ( const char * title )
{
    ssize_t len = strlen(title);
    xcb_change_property ( xcb->connection, XCB_PROP_MODE_REPLACE, CacheState.main_window, xcb->ewmh._NET_WM_NAME, xcb->ewmh.UTF8_STRING, 8, len, title );
    xcb_change_property ( xcb->connection, XCB_PROP_MODE_REPLACE, CacheState.main_window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, len, title );
}