#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_inhibit_t ;
struct TYPE_5__ {int /*<<< orphan*/  attr; } ;
typedef  TYPE_2__ vlc_inhibit_sys_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  environ ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int posix_spawnp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror_c (int) ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Timer (void *data)
{
    vlc_inhibit_t *ih = data;
    vlc_inhibit_sys_t *sys = ih->p_sys;
    char *argv[3] = {
        (char *)"xdg-screensaver", (char *)"reset", NULL
    };
    pid_t pid;

    int err = posix_spawnp (&pid, "xdg-screensaver", NULL, &sys->attr,
                            argv, environ);
    if (err == 0)
    {
        int status;

        while (waitpid (pid, &status, 0) == -1);
    }
    else
        msg_Warn (ih, "error starting xdg-screensaver: %s",
                  vlc_strerror_c(err));
}