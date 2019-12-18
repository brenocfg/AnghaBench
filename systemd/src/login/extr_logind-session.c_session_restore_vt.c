#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vtfd; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int EIO ; 
 int TAKE_FD (int) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int safe_close (int) ; 
 int session_open_vt (TYPE_1__*) ; 
 int vt_restore (int) ; 

__attribute__((used)) static void session_restore_vt(Session *s) {
        int r;

        r = vt_restore(s->vtfd);
        if (r == -EIO) {
                int vt, old_fd;

                /* It might happen if the controlling process exited before or while we were
                 * restoring the VT as it would leave the old file-descriptor in a hung-up
                 * state. In this case let's retry with a fresh handle to the virtual terminal. */

                /* We do a little dance to avoid having the terminal be available
                 * for reuse before we've cleaned it up. */
                old_fd = TAKE_FD(s->vtfd);

                vt = session_open_vt(s);
                safe_close(old_fd);

                if (vt >= 0)
                        r = vt_restore(vt);
        }

        if (r < 0)
                log_warning_errno(r, "Failed to restore VT, ignoring: %m");

        s->vtfd = safe_close(s->vtfd);
}