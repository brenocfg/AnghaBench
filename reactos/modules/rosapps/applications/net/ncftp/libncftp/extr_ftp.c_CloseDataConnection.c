#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dataSocket; scalar_t__ xferTimeout; int /*<<< orphan*/  servDataAddr; int /*<<< orphan*/  ourDataAddr; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  SClose (scalar_t__,int) ; 
 int /*<<< orphan*/  alarm (scalar_t__) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ kClosedFileDescriptor ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
CloseDataConnection(const FTPCIPtr cip)
{
	if (cip->dataSocket != kClosedFileDescriptor) {
#ifdef NO_SIGNALS
		SClose(cip->dataSocket, 3);
#else	/* NO_SIGNALS */
		if (cip->xferTimeout > 0)
			(void) alarm(cip->xferTimeout);
		(void) closesocket(cip->dataSocket);
		if (cip->xferTimeout > 0)
			(void) alarm(0);
#endif	/* NO_SIGNALS */
		cip->dataSocket = kClosedFileDescriptor;
	}
	memset(&cip->ourDataAddr, 0, sizeof(cip->ourDataAddr));
	memset(&cip->servDataAddr, 0, sizeof(cip->servDataAddr));
}