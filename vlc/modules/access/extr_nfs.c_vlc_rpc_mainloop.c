#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct rpc_context {int dummy; } ;
struct pollfd {scalar_t__ revents; int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_9__ {int b_error; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  rpc_get_fd (struct rpc_context*) ; 
 scalar_t__ rpc_service (struct rpc_context*,scalar_t__) ; 
 int /*<<< orphan*/  rpc_which_events (struct rpc_context*) ; 
 int vlc_poll_i11e (struct pollfd*,int,int) ; 

__attribute__((used)) static int
vlc_rpc_mainloop(stream_t *p_access, struct rpc_context *p_rpc_ctx,
                 bool (*pf_until_cb)(stream_t *))
{
    access_sys_t *p_sys = p_access->p_sys;

    while (!p_sys->b_error && !pf_until_cb(p_access))
    {
        struct pollfd p_fds[1];
        int i_ret;
        p_fds[0].fd = rpc_get_fd(p_rpc_ctx);
        p_fds[0].events = rpc_which_events(p_rpc_ctx);

        if ((i_ret = vlc_poll_i11e(p_fds, 1, -1)) < 0)
        {
            if (errno == EINTR)
                msg_Warn(p_access, "vlc_poll_i11e interrupted");
            else
                msg_Err(p_access, "vlc_poll_i11e failed");
            p_sys->b_error = true;
        }
        else if (i_ret > 0 && p_fds[0].revents
             && rpc_service(p_rpc_ctx, p_fds[0].revents) < 0)
        {
            msg_Err(p_access, "nfs_service failed");
            p_sys->b_error = true;
        }
    }
    return p_sys->b_error ? -1 : 0;
}