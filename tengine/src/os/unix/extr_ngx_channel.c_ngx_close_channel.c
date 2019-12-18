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
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_fd_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void
ngx_close_channel(ngx_fd_t *fd, ngx_log_t *log)
{
    if (close(fd[0]) == -1) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno, "close() channel failed");
    }

    if (close(fd[1]) == -1) {
        ngx_log_error(NGX_LOG_ALERT, log, ngx_errno, "close() channel failed");
    }
}