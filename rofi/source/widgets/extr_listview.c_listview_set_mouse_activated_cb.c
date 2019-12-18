#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listview_mouse_activated_cb ;
struct TYPE_3__ {void* mouse_activated_data; int /*<<< orphan*/  mouse_activated; } ;
typedef  TYPE_1__ listview ;

/* Variables and functions */

void listview_set_mouse_activated_cb ( listview *lv, listview_mouse_activated_cb cb, void *udata )
{
    if ( lv ) {
        lv->mouse_activated      = cb;
        lv->mouse_activated_data = udata;
    }
}