#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_pid_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  size_t ngx_int_t ;
struct TYPE_4__ {int fd; int /*<<< orphan*/  command; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ ngx_channel_t ;
struct TYPE_5__ {int pid; int /*<<< orphan*/ * channel; scalar_t__ detached; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_CMD_PIPE_BROKEN ; 
 size_t ngx_last_process ; 
 TYPE_3__* ngx_processes ; 
 int /*<<< orphan*/  ngx_write_channel (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_signal_pipe_broken(ngx_log_t *log, ngx_pid_t pid)
{
    ngx_int_t      i;
    ngx_channel_t  ch;

    ch.fd = -1;
    ch.pid = pid;
    ch.command = NGX_CMD_PIPE_BROKEN;

    for (i = 0; i < ngx_last_process; i++) {

        if (ngx_processes[i].detached || ngx_processes[i].pid == -1) {
            continue;
        }

        ngx_write_channel(ngx_processes[i].channel[0],
                          &ch, sizeof(ngx_channel_t), log);
    }
}