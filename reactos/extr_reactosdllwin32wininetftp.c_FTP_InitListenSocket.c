#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
struct TYPE_4__ {int /*<<< orphan*/  sin_port; } ;
struct TYPE_5__ {int lstnSocket; TYPE_1__ lstnSocketAddress; TYPE_1__ socketAddress; } ;
typedef  TYPE_2__ ftp_session_t ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAX_BACKLOG ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_winsock () ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL FTP_InitListenSocket(ftp_session_t *lpwfs)
{
    BOOL bSuccess = FALSE;
    socklen_t namelen = sizeof(lpwfs->lstnSocketAddress);

    TRACE("\n");

    init_winsock();
    lpwfs->lstnSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (lpwfs->lstnSocket == -1)
    {
        TRACE("Unable to create listening socket\n");
            goto lend;
    }

    /* We obtain our ip addr from the name of the command channel socket */
    lpwfs->lstnSocketAddress = lpwfs->socketAddress;

    /* and get the system to assign us a port */
    lpwfs->lstnSocketAddress.sin_port = htons(0);

    if (bind(lpwfs->lstnSocket,(struct sockaddr *) &lpwfs->lstnSocketAddress, sizeof(lpwfs->lstnSocketAddress)) == -1)
    {
        TRACE("Unable to bind socket\n");
        goto lend;
    }

    if (listen(lpwfs->lstnSocket, MAX_BACKLOG) == -1)
    {
        TRACE("listen failed\n");
        goto lend;
    }

    if (getsockname(lpwfs->lstnSocket, (struct sockaddr *) &lpwfs->lstnSocketAddress, &namelen) != -1)
        bSuccess = TRUE;

lend:
    if (!bSuccess && lpwfs->lstnSocket != -1)
    {
        closesocket(lpwfs->lstnSocket);
        lpwfs->lstnSocket = -1;
    }

    return bSuccess;
}