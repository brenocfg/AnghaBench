#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  child_info_data; int /*<<< orphan*/ * child_info_pipe; } ;

/* Variables and functions */
 scalar_t__ ANET_OK ; 
 scalar_t__ anetNonBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closeChildInfoPipe () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pipe (int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 

void openChildInfoPipe(void) {
    if (pipe(server.child_info_pipe) == -1) {
        /* On error our two file descriptors should be still set to -1,
         * but we call anyway cloesChildInfoPipe() since can't hurt. */
        closeChildInfoPipe();
    } else if (anetNonBlock(NULL,server.child_info_pipe[0]) != ANET_OK) {
        closeChildInfoPipe();
    } else {
        memset(&server.child_info_data,0,sizeof(server.child_info_data));
    }
}