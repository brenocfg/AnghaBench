#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_13__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_11__ {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_12__ {scalar_t__ dataPortMode; int dataSocket; scalar_t__ connTimeout; int errNo; scalar_t__ require20; TYPE_3__ servCtlAddr; TYPE_5__ servDataAddr; } ;
typedef  TYPE_4__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  Error (TYPE_4__* const,int /*<<< orphan*/ ,char*) ; 
 int SAccept (int,TYPE_5__*,int) ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  alarm (scalar_t__) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 void* kClosedFileDescriptor ; 
 int /*<<< orphan*/  kDoPerror ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrAcceptDataSocket ; 
 scalar_t__ kSendPortMode ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 

int
AcceptDataConnection(const FTPCIPtr cip)
{
	int newSocket;
#ifndef NO_SIGNALS
	int len;
#endif
	unsigned short remoteDataPort;
	unsigned short remoteCtrlPort;

	/* If we did a PORT, we have some things to finish up.
	 * If we did a PASV, we're ready to go.
	 */
	if (cip->dataPortMode == kSendPortMode) {
		/* Accept will give us back the server's data address;  at the
		 * moment we don't do anything with it though.
		 */
		memset(&cip->servDataAddr, 0, sizeof(cip->servDataAddr));

#ifdef NO_SIGNALS
		newSocket = SAccept(cip->dataSocket, &cip->servDataAddr, (int) cip->connTimeout);
#else	/* NO_SIGNALS */
		len = (int) sizeof(cip->servDataAddr);
		if (cip->connTimeout > 0)
			(void) alarm(cip->connTimeout);
		newSocket = accept(cip->dataSocket, (struct sockaddr *) &cip->servDataAddr, &len);
		if (cip->connTimeout > 0)
			(void) alarm(0);
#endif	/* NO_SIGNALS */

		(void) closesocket(cip->dataSocket);
		if (newSocket < 0) {
			Error(cip, kDoPerror, "Could not accept a data connection.\n");
			cip->dataSocket = kClosedFileDescriptor;
			cip->errNo = kErrAcceptDataSocket;
			return (kErrAcceptDataSocket);
		}

		if (cip->require20 != 0) {
			remoteDataPort = ntohs(cip->servDataAddr.sin_port);
			remoteCtrlPort = ntohs(cip->servCtlAddr.sin_port);
			if ((int) remoteDataPort != ((int) remoteCtrlPort - 1)) {
				Error(cip, kDontPerror, "Data connection did not originate on correct port!\n");
				(void) closesocket(newSocket);
				cip->dataSocket = kClosedFileDescriptor;
				cip->errNo = kErrAcceptDataSocket;
				return (kErrAcceptDataSocket);
			} else if (memcmp(&cip->servDataAddr.sin_addr.s_addr, &cip->servCtlAddr.sin_addr.s_addr, sizeof(cip->servDataAddr.sin_addr.s_addr)) != 0) {
				Error(cip, kDontPerror, "Data connection did not originate from remote server!\n");
				(void) closesocket(newSocket);
				cip->dataSocket = kClosedFileDescriptor;
				cip->errNo = kErrAcceptDataSocket;
				return (kErrAcceptDataSocket);
			}
		}

		cip->dataSocket = newSocket;
	}

	return (0);
}