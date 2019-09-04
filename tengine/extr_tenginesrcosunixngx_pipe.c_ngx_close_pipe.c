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
struct TYPE_3__ {int pid; scalar_t__ configured; } ;
typedef  TYPE_1__ ngx_open_pipe_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_close_pipe(ngx_open_pipe_t *pipe)
{
    /*
     * No waitpid at this place, because it is called at
     * ngx_process_get_status first.
     */

    if (pipe->pid != -1) {
        kill(pipe->pid, SIGTERM);
    }

    pipe->configured = 0;
}