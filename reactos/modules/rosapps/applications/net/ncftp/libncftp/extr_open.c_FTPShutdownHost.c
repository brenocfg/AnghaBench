#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dataSocket; int /*<<< orphan*/  magic; } ;
typedef  scalar_t__ FTPSigProc ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  CloseControlConnection (TYPE_1__* const) ; 
 int /*<<< orphan*/  CloseDataConnection (TYPE_1__* const) ; 
 int /*<<< orphan*/  FTPDeallocateHost (TYPE_1__* const) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  SetLinger (TYPE_1__* const,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kClosedFileDescriptor ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 scalar_t__ signal (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
FTPShutdownHost(const FTPCIPtr cip)
{
#ifdef SIGPIPE
	FTPSigProc osigpipe;
#endif

	if (cip == NULL)
		return;
	if (strcmp(cip->magic, kLibraryMagic))
		return;

#ifdef SIGPIPE
	osigpipe = signal(SIGPIPE, (FTPSigProc) SIG_IGN);
#endif

	/* Linger could cause close to block, so unset it. */
	if (cip->dataSocket != kClosedFileDescriptor)
		(void) SetLinger(cip, cip->dataSocket, 0);
	CloseDataConnection(cip);	/* Shouldn't be open normally. */

	/* Linger should already be turned off for this. */
	CloseControlConnection(cip);

	FTPDeallocateHost(cip);

#ifdef SIGPIPE
	(void) signal(SIGPIPE, (FTPSigProc) osigpipe);
#endif
}