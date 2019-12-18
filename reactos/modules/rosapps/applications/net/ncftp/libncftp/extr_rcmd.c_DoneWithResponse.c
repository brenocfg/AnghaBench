#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  (* printResponseProc ) (TYPE_2__* const,TYPE_1__*) ;} ;
struct TYPE_13__ {int printMode; int /*<<< orphan*/  msg; } ;
typedef  TYPE_1__* ResponsePtr ;
typedef  int /*<<< orphan*/  Response ;
typedef  TYPE_2__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DisposeLineListContents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SaveLastResponse (TYPE_2__* const,TYPE_1__*) ; 
 int /*<<< orphan*/  TraceResponse (TYPE_2__* const,TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int kResponseNoProc ; 
 int kResponseNoSave ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__* const,TYPE_1__*) ; 

void
DoneWithResponse(const FTPCIPtr cip, ResponsePtr rp)
{
	/* Dispose space taken up by the Response, and clear it out
	 * again.  For some reason, I like to return memory to zeroed
	 * when not in use.
	 */
	if (rp != NULL) {
		TraceResponse(cip, rp);
		if (cip->printResponseProc != 0) {
			if ((rp->printMode & kResponseNoProc) == 0)
				(*cip->printResponseProc)(cip, rp);
		}
		if ((rp->printMode & kResponseNoSave) == 0)
			SaveLastResponse(cip, rp);
		else
			DisposeLineListContents(&rp->msg);
		(void) memset(rp, 0, sizeof(Response));
		free(rp);
	}
}