#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ connected; scalar_t__ loggedIn; int ctrlTimeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTPCloseHost (TYPE_1__*) ; 
 int /*<<< orphan*/  RunBatchIfNeeded (TYPE_1__*) ; 
 int /*<<< orphan*/  SaveUnsavedBookmark () ; 
 TYPE_1__ gConn ; 

void
CloseHost(void)
{
	if (gConn.connected != 0) {
		if (gConn.loggedIn != 0) {
			SaveUnsavedBookmark();
		}
		RunBatchIfNeeded(&gConn);
	}
	gConn.ctrlTimeout = 3;
	(void) FTPCloseHost(&gConn);
}