#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dwContext; } ;
struct TYPE_9__ {int lstnSocket; TYPE_1__ hdr; int /*<<< orphan*/  sndSocket; } ;
typedef  TYPE_2__ ftp_session_t ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTP_CMD_RETR ; 
 int /*<<< orphan*/  FTP_InitListenSocket (TYPE_2__*) ; 
 int FTP_ReceiveResponse (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SendPortOrPasv (TYPE_2__*) ; 
 int /*<<< orphan*/  FTP_SendType (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SetResponseError (int) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  closesocket (int) ; 

__attribute__((used)) static BOOL FTP_SendRetrieve(ftp_session_t *lpwfs, LPCWSTR lpszRemoteFile, DWORD dwType)
{
    INT nResCode;
    BOOL ret;

    TRACE("\n");
    if (!(ret = FTP_InitListenSocket(lpwfs)))
        goto lend;

    if (!(ret = FTP_SendType(lpwfs, dwType)))
        goto lend;

    if (!(ret = FTP_SendPortOrPasv(lpwfs)))
        goto lend;

    if (!(ret = FTP_SendCommand(lpwfs->sndSocket, FTP_CMD_RETR, lpszRemoteFile, 0, 0, 0)))
        goto lend;

    nResCode = FTP_ReceiveResponse(lpwfs, lpwfs->hdr.dwContext);
    if ((nResCode != 125) && (nResCode != 150)) {
	/* That means that we got an error getting the file. */
        FTP_SetResponseError(nResCode);
	ret = FALSE;
    }

lend:
    if (!ret && lpwfs->lstnSocket != -1)
    {
        closesocket(lpwfs->lstnSocket);
        lpwfs->lstnSocket = -1;
    }

    return ret;
}