#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* first; } ;
struct TYPE_9__ {char* lastFTPCmdResultStr; int lastFTPCmdResultNum; TYPE_6__ lastFTPCmdResultLL; } ;
struct TYPE_8__ {int code; TYPE_6__ msg; } ;
struct TYPE_7__ {int /*<<< orphan*/ * line; } ;
typedef  TYPE_2__* ResponsePtr ;
typedef  TYPE_3__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DisposeLineListContents (TYPE_6__*) ; 
 int /*<<< orphan*/  STRNCPY (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
SaveLastResponse(const FTPCIPtr cip, ResponsePtr rp)
{
	if (rp == NULL) {
		cip->lastFTPCmdResultStr[0] = '\0';
		cip->lastFTPCmdResultNum = -1;
		DisposeLineListContents(&cip->lastFTPCmdResultLL);
	} else if ((rp->msg.first == NULL) || (rp->msg.first->line == NULL)) {
		cip->lastFTPCmdResultStr[0] = '\0';
		cip->lastFTPCmdResultNum = rp->code;
		DisposeLineListContents(&cip->lastFTPCmdResultLL);
	} else {
		(void) STRNCPY(cip->lastFTPCmdResultStr, rp->msg.first->line);
		cip->lastFTPCmdResultNum = rp->code;

		/* Dispose previous command's line list. */
		DisposeLineListContents(&cip->lastFTPCmdResultLL);

		/* Save this command's line list. */
		cip->lastFTPCmdResultLL = rp->msg;
	}
}