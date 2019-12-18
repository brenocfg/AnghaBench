#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {int /*<<< orphan*/  repo_id; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ WatchCommand ;
struct TYPE_7__ {int /*<<< orphan*/ * cmd_pipe; } ;
typedef  TYPE_2__ SeafWTMonitor ;
typedef  int /*<<< orphan*/  CFOptionFlags ;
typedef  int /*<<< orphan*/  CFFileDescriptorRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFFileDescriptorEnableCallBacks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CFRunLoopGetCurrent () ; 
 int /*<<< orphan*/  handle_watch_command (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  kCFFileDescriptorReadCallBack ; 
 int /*<<< orphan*/  seaf_debug (char*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int seaf_pipe_readn (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

__attribute__((used)) static void
command_read_cb (CFFileDescriptorRef fdref,
                             CFOptionFlags callBackTypes,
                             void *info)
{
    SeafWTMonitor *monitor = (SeafWTMonitor *)info;
    WatchCommand cmd;
    int n;

    n = seaf_pipe_readn (monitor->cmd_pipe[0], &cmd, sizeof(cmd));
    if (n != sizeof(cmd)) {
        seaf_warning ("[wt mon] failed to read command.\n");
        CFFileDescriptorEnableCallBacks (fdref, kCFFileDescriptorReadCallBack);
        return;
    }

    seaf_debug ("[wt mon] %ld receive command type=%d, repo=%s\n",
                (long)CFRunLoopGetCurrent(), cmd.type, cmd.repo_id);
    handle_watch_command (monitor, &cmd);
    CFFileDescriptorEnableCallBacks (fdref, kCFFileDescriptorReadCallBack);
}