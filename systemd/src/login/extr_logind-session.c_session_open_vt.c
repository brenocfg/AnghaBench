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
struct TYPE_3__ {int vtnr; scalar_t__ vtfd; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  DECIMAL_STR_MAX (int) ; 
 int ENODEV ; 
 int O_CLOEXEC ; 
 int O_NOCTTY ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int log_error_errno (scalar_t__,char*,char*,int /*<<< orphan*/ ) ; 
 int open_terminal (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int session_open_vt(Session *s) {
        char path[sizeof("/dev/tty") + DECIMAL_STR_MAX(s->vtnr)];

        if (s->vtnr < 1)
                return -ENODEV;

        if (s->vtfd >= 0)
                return s->vtfd;

        sprintf(path, "/dev/tty%u", s->vtnr);
        s->vtfd = open_terminal(path, O_RDWR | O_CLOEXEC | O_NONBLOCK | O_NOCTTY);
        if (s->vtfd < 0)
                return log_error_errno(s->vtfd, "cannot open VT %s of session %s: %m", path, s->id);

        return s->vtfd;
}