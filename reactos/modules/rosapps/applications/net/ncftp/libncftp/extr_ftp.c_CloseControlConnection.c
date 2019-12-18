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
struct TYPE_3__ {scalar_t__ ctrlTimeout; scalar_t__ loggedIn; scalar_t__ connected; void* ctrlSocketW; void* ctrlSocketR; int /*<<< orphan*/  cout; int /*<<< orphan*/  cin; int /*<<< orphan*/  ctrlSrl; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  CloseFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DisposeSReadlineInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SClose (void*,int) ; 
 int /*<<< orphan*/  alarm (scalar_t__) ; 
 void* kClosedFileDescriptor ; 

void
CloseControlConnection(const FTPCIPtr cip)
{
	/* This will close each file, if it was open. */
#ifdef NO_SIGNALS
	SClose(cip->ctrlSocketR, 3);
	cip->ctrlSocketR = kClosedFileDescriptor;
	cip->ctrlSocketW = kClosedFileDescriptor;
	DisposeSReadlineInfo(&cip->ctrlSrl);
#else	/* NO_SIGNALS */
	if (cip->ctrlTimeout > 0)
		(void) alarm(cip->ctrlTimeout);
	CloseFile(&cip->cin);
	CloseFile(&cip->cout);
	cip->ctrlSocketR = kClosedFileDescriptor;
	cip->ctrlSocketW = kClosedFileDescriptor;
	if (cip->ctrlTimeout > 0)
		(void) alarm(0);
#endif	/* NO_SIGNALS */
	cip->connected = 0;
	cip->loggedIn = 0;
}