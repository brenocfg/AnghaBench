#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dwContext; } ;
struct TYPE_6__ {TYPE_1__ hdr; int /*<<< orphan*/  sndSocket; } ;
typedef  TYPE_2__ ftp_session_t ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTP_CMD_ACCT ; 
 scalar_t__ FTP_ReceiveResponse (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SetResponseError (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  szNoAccount ; 

__attribute__((used)) static BOOL FTP_SendAccount(ftp_session_t *lpwfs)
{
    INT nResCode;
    BOOL bSuccess = FALSE;

    TRACE("\n");
    if (!FTP_SendCommand(lpwfs->sndSocket, FTP_CMD_ACCT, szNoAccount, 0, 0, 0))
        goto lend;

    nResCode = FTP_ReceiveResponse(lpwfs, lpwfs->hdr.dwContext);
    if (nResCode)
        bSuccess = TRUE;
    else
        FTP_SetResponseError(nResCode);

lend:
    return bSuccess;
}