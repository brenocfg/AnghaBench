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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ) ; 
 int errno ; 

__attribute__((used)) static void write_confirm_error_fd(int err, int fd, const Unit *u) {
        assert(err < 0);

        if (err == -ETIMEDOUT)
                dprintf(fd, "Confirmation question timed out for %s, assuming positive response.\n", u->id);
        else {
                errno = -err;
                dprintf(fd, "Couldn't ask confirmation for %s: %m, assuming positive response.\n", u->id);
        }
}