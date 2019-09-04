#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t bufSize; int /*<<< orphan*/  user; int /*<<< orphan*/  magic; int /*<<< orphan*/ * startingWorkingDirectory; int /*<<< orphan*/  firewallType; void* NLSTfileParamWorks; void* STATfileParamWorks; void* hasSBUFSZ; void* hasSBUFSIZ; void* hasSTORBUFSIZE; void* hasRBUFSZ; void* hasRBUFSIZ; void* hasRETRBUFSIZE; void* hasCLNT; void* hasMLST; void* hasMLSD; void* hasFEAT; void* hasUTIME; void* hasNLST_d; void* hasREST; void* hasMDTM; void* hasSIZE; void* hasPASV; TYPE_1__* lip; void* dataSocket; int /*<<< orphan*/  dataPortMode; void* ctrlSocketW; void* ctrlSocketR; int /*<<< orphan*/  abortTimeout; int /*<<< orphan*/  ctrlTimeout; int /*<<< orphan*/  connTimeout; int /*<<< orphan*/  xferTimeout; int /*<<< orphan*/  redialDelay; int /*<<< orphan*/  maxDials; int /*<<< orphan*/  firewallPort; int /*<<< orphan*/  port; int /*<<< orphan*/ * buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  defaultPort; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__* FTPLIPtr ;
typedef  int /*<<< orphan*/  FTPConnectionInfo ;
typedef  TYPE_2__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ ,char*) ; 
 void* kClosedFileDescriptor ; 
 void* kCommandAvailabilityUnknown ; 
 int /*<<< orphan*/  kDefaultAbortTimeout ; 
 int /*<<< orphan*/  kDefaultConnTimeout ; 
 int /*<<< orphan*/  kDefaultCtrlTimeout ; 
 int /*<<< orphan*/  kDefaultMaxDials ; 
 int /*<<< orphan*/  kDefaultRedialDelay ; 
 int /*<<< orphan*/  kDefaultXferTimeout ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int /*<<< orphan*/  kFirewallNotInUse ; 
 char* kLibraryMagic ; 
 int kNoErr ; 
 int /*<<< orphan*/  kSendPortMode ; 
 int /*<<< orphan*/  memset (TYPE_2__* const,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
FTPInitConnectionInfo(const FTPLIPtr lip, const FTPCIPtr cip, size_t bufSize)
{
	size_t siz;

	if ((lip == NULL) || (cip == NULL) || (bufSize == 0))
		return (kErrBadParameter);

	siz = sizeof(FTPConnectionInfo);
	(void) memset(cip, 0, siz);

	if (strcmp(lip->magic, kLibraryMagic))
		return (kErrBadMagic);

	cip->buf = NULL;	/* denote that it needs to be allocated. */
	cip->bufSize = bufSize;
	cip->port = lip->defaultPort;
	cip->firewallPort = lip->defaultPort;
	cip->maxDials = kDefaultMaxDials;
	cip->redialDelay = kDefaultRedialDelay;
	cip->xferTimeout = kDefaultXferTimeout;
	cip->connTimeout = kDefaultConnTimeout;
	cip->ctrlTimeout = kDefaultCtrlTimeout;
	cip->abortTimeout = kDefaultAbortTimeout;
	cip->ctrlSocketR = kClosedFileDescriptor;
	cip->ctrlSocketW = kClosedFileDescriptor;
	cip->dataPortMode = kSendPortMode;
	cip->dataSocket = kClosedFileDescriptor;
	cip->lip = lip;
	cip->hasPASV = kCommandAvailabilityUnknown;
	cip->hasSIZE = kCommandAvailabilityUnknown;
	cip->hasMDTM = kCommandAvailabilityUnknown;
	cip->hasREST = kCommandAvailabilityUnknown;
	cip->hasNLST_d = kCommandAvailabilityUnknown;
	cip->hasUTIME = kCommandAvailabilityUnknown;
	cip->hasFEAT = kCommandAvailabilityUnknown;
	cip->hasMLSD = kCommandAvailabilityUnknown;
	cip->hasMLST = kCommandAvailabilityUnknown;
	cip->hasCLNT = kCommandAvailabilityUnknown;
	cip->hasRETRBUFSIZE = kCommandAvailabilityUnknown;
	cip->hasRBUFSIZ = kCommandAvailabilityUnknown;
	cip->hasRBUFSZ = kCommandAvailabilityUnknown;
	cip->hasSTORBUFSIZE = kCommandAvailabilityUnknown;
	cip->hasSBUFSIZ = kCommandAvailabilityUnknown;
	cip->hasSBUFSZ = kCommandAvailabilityUnknown;
	cip->STATfileParamWorks = kCommandAvailabilityUnknown;
	cip->NLSTfileParamWorks = kCommandAvailabilityUnknown;
	cip->firewallType = kFirewallNotInUse;
	cip->startingWorkingDirectory = NULL;
	(void) STRNCPY(cip->magic, kLibraryMagic);
	(void) STRNCPY(cip->user, "anonymous");
	return (kNoErr);
}