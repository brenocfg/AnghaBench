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
struct logger {scalar_t__ fd; } ;

/* Variables and functions */
 scalar_t__ STDERR_FILENO ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 struct logger logger ; 

void
log_deinit(void)
{
    struct logger *l = &logger;

    if (l->fd < 0 || l->fd == STDERR_FILENO) {
        return;
    }

    close(l->fd);
}