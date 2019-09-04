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
struct TYPE_2__ {int repl_transfer_s; int /*<<< orphan*/  el; } ;

/* Variables and functions */
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ server ; 

void undoConnectWithMaster(void) {
    int fd = server.repl_transfer_s;

    aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
    close(fd);
    server.repl_transfer_s = -1;
}