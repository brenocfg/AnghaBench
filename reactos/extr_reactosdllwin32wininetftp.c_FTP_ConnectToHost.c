#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dwContext; } ;
struct TYPE_8__ {TYPE_1__ hdr; int /*<<< orphan*/  lpszUserName; int /*<<< orphan*/  sndSocket; } ;
typedef  TYPE_2__ ftp_session_t ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTP_CMD_USER ; 
 int FTP_ReceiveResponse (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SendAccount (TYPE_2__*) ; 
 int /*<<< orphan*/  FTP_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SendPassword (TYPE_2__*) ; 
 int /*<<< orphan*/  FTP_SetResponseError (int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL FTP_ConnectToHost(ftp_session_t *lpwfs)
{
    INT nResCode;
    BOOL bSuccess = FALSE;

    TRACE("\n");
    FTP_ReceiveResponse(lpwfs, lpwfs->hdr.dwContext);

    if (!FTP_SendCommand(lpwfs->sndSocket, FTP_CMD_USER, lpwfs->lpszUserName, 0, 0, 0))
        goto lend;

    nResCode = FTP_ReceiveResponse(lpwfs, lpwfs->hdr.dwContext);
    if (nResCode)
    {
        /* Login successful... */
        if (nResCode == 230)
            bSuccess = TRUE;
        /* User name okay, need password... */
        else if (nResCode == 331)
            bSuccess = FTP_SendPassword(lpwfs);
        /* Need account for login... */
        else if (nResCode == 332)
            bSuccess = FTP_SendAccount(lpwfs);
        else
            FTP_SetResponseError(nResCode);
    }

    TRACE("Returning %d\n", bSuccess);
lend:
    return bSuccess;
}