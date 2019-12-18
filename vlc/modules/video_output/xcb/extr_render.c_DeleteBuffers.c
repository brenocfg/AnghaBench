#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_8__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ vout_display_t ;
struct TYPE_7__ {int /*<<< orphan*/  crop; int /*<<< orphan*/  scale; } ;
struct TYPE_6__ {int /*<<< orphan*/  crop; int /*<<< orphan*/  scale; } ;
struct TYPE_9__ {TYPE_2__ drawable; TYPE_1__ picture; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_4__ vout_display_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  xcb_free_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_render_free_picture (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DeleteBuffers(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;
    xcb_connection_t *conn = sys->conn;

    xcb_render_free_picture(conn, sys->picture.scale);
    xcb_render_free_picture(conn, sys->picture.crop);
    xcb_free_pixmap(conn, sys->drawable.scale);
    xcb_free_pixmap(conn, sys->drawable.crop);
}