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
typedef  char WCHAR ;
typedef  int INT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTP_CMD_TYPE ; 
 int FTP_ReceiveResponse (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SetResponseError (int) ; 
 int INTERNET_FLAG_TRANSFER_ASCII ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL FTP_SendType(ftp_session_t *lpwfs, DWORD dwType)
{
    INT nResCode;
    WCHAR type[] = { 'I','\0' };
    BOOL bSuccess = FALSE;

    TRACE("\n");
    if (dwType & INTERNET_FLAG_TRANSFER_ASCII)
        type[0] = 'A';

    if (!FTP_SendCommand(lpwfs->sndSocket, FTP_CMD_TYPE, type, 0, 0, 0))
        goto lend;

    nResCode = FTP_ReceiveResponse(lpwfs, lpwfs->hdr.dwContext)/100;
    if (nResCode)
    {
        if (nResCode == 2)
            bSuccess = TRUE;
	else
            FTP_SetResponseError(nResCode);
    }

lend:
    return bSuccess;
}