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
struct logger {scalar_t__ fd; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 scalar_t__ STDERR_FILENO ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_stderr_safe (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct logger logger ; 
 scalar_t__ open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
log_reopen(void)
{
    struct logger *l = &logger;

    if (l->fd != STDERR_FILENO) {
        close(l->fd);
        l->fd = open(l->name, O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (l->fd < 0) {
            log_stderr_safe("reopening log file '%s' failed, ignored: %s", l->name,
                       strerror(errno));
        }
    }
}