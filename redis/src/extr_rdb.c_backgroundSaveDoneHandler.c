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
struct TYPE_2__ {int rdb_child_type; } ;

/* Variables and functions */
#define  RDB_CHILD_TYPE_DISK 129 
#define  RDB_CHILD_TYPE_SOCKET 128 
 int /*<<< orphan*/  backgroundSaveDoneHandlerDisk (int,int) ; 
 int /*<<< orphan*/  backgroundSaveDoneHandlerSocket (int,int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

void backgroundSaveDoneHandler(int exitcode, int bysignal) {
    switch(server.rdb_child_type) {
    case RDB_CHILD_TYPE_DISK:
        backgroundSaveDoneHandlerDisk(exitcode,bysignal);
        break;
    case RDB_CHILD_TYPE_SOCKET:
        backgroundSaveDoneHandlerSocket(exitcode,bysignal);
        break;
    default:
        serverPanic("Unknown RDB child type.");
        break;
    }
}