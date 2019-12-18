#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  size_t ssize_t ;
struct TYPE_8__ {TYPE_1__* manager; } ;
struct TYPE_7__ {int /*<<< orphan*/  console_active_fd; } ;
typedef  TYPE_2__ Seat ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int errno ; 
 int /*<<< orphan*/  log_error (char*,char*) ; 
 int log_error_errno (int,char*) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t read (int /*<<< orphan*/ ,char*,int) ; 
 int seat_active_vt_changed (TYPE_2__*,int) ; 
 int /*<<< orphan*/  seat_has_vts (TYPE_2__*) ; 
 char* strerror_safe (int) ; 
 int /*<<< orphan*/  truncate_nl (char*) ; 
 int vtnr_from_tty (char*) ; 

int seat_read_active_vt(Seat *s) {
        char t[64];
        ssize_t k;
        int vtnr;

        assert(s);

        if (!seat_has_vts(s))
                return 0;

        if (lseek(s->manager->console_active_fd, SEEK_SET, 0) < 0)
                return log_error_errno(errno, "lseek on console_active_fd failed: %m");

        k = read(s->manager->console_active_fd, t, sizeof(t)-1);
        if (k <= 0) {
                log_error("Failed to read current console: %s", k < 0 ? strerror_safe(errno) : "EOF");
                return k < 0 ? -errno : -EIO;
        }

        t[k] = 0;
        truncate_nl(t);

        vtnr = vtnr_from_tty(t);
        if (vtnr < 0) {
                log_error_errno(vtnr, "Hm, /sys/class/tty/tty0/active is badly formatted: %m");
                return -EIO;
        }

        return seat_active_vt_changed(s, vtnr);
}