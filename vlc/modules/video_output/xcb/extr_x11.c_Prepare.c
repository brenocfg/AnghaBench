#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_void_cookie_t ;
typedef  int /*<<< orphan*/  xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_7__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_8__ {int attached; scalar_t__ segment; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
struct TYPE_9__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_10__ {int fd; } ;
typedef  TYPE_4__ picture_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int vlc_dup (int) ; 
 int /*<<< orphan*/ * xcb_request_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_shm_attach_fd_checked (int /*<<< orphan*/ *,scalar_t__,int,int) ; 

__attribute__((used)) static void Prepare(vout_display_t *vd, picture_t *pic, subpicture_t *subpic,
                    vlc_tick_t date)
{
    vout_display_sys_t *sys = vd->sys;
    const picture_buffer_t *buf = pic->p_sys;
    xcb_connection_t *conn = sys->conn;

    sys->attached = false;

    if (sys->segment == 0)
        return; /* SHM extension not supported */
    if (buf->fd == -1)
        return; /* not a shareable picture buffer */

    int fd = vlc_dup(buf->fd);
    if (fd == -1)
        return;

    xcb_void_cookie_t c = xcb_shm_attach_fd_checked(conn, sys->segment, fd, 1);
    xcb_generic_error_t *e = xcb_request_check(conn, c);
    if (e != NULL) /* attach failure (likely remote access) */
    {
        free(e);
        return;
    }

    sys->attached = true;
    (void) subpic; (void) date;
}