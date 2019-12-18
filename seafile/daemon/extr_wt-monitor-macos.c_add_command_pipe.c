#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; TYPE_1__* member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cmd_pipe; } ;
typedef  TYPE_1__ SeafWTMonitor ;
typedef  int /*<<< orphan*/  CFRunLoopSourceRef ;
typedef  int /*<<< orphan*/ * CFFileDescriptorRef ;
typedef  TYPE_2__ CFFileDescriptorContext ;

/* Variables and functions */
 int /*<<< orphan*/ * CFFileDescriptorCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CFFileDescriptorCreateRunLoopSource (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFFileDescriptorEnableCallBacks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRunLoopAddSource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRunLoopGetCurrent () ; 
 int /*<<< orphan*/  command_read_cb ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFFileDescriptorReadCallBack ; 
 int /*<<< orphan*/  kCFRunLoopDefaultMode ; 

__attribute__((used)) static int
add_command_pipe (SeafWTMonitor *monitor)
{
    CFFileDescriptorContext ctx = {0, monitor, NULL, NULL, NULL};
    CFFileDescriptorRef fdref = CFFileDescriptorCreate(NULL,
                                                       monitor->cmd_pipe[0], true,
                                                       command_read_cb, &ctx);
    if (fdref == NULL) {
        return -1;
    }

    CFFileDescriptorEnableCallBacks(fdref, kCFFileDescriptorReadCallBack);
    CFRunLoopSourceRef source = CFFileDescriptorCreateRunLoopSource(kCFAllocatorDefault, fdref, 0);
    CFRunLoopAddSource (CFRunLoopGetCurrent(), source, kCFRunLoopDefaultMode);
    CFRelease(source);
    return 0;
}