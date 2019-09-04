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
struct TYPE_3__ {int bIsDirectory; unsigned short permissions; } ;
typedef  TYPE_1__* LPFILEPROPERTIESW ;
typedef  char* LPCSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL FTP_ParsePermission(LPCSTR lpszPermission, LPFILEPROPERTIESW lpfp)
{
    BOOL bSuccess = TRUE;
    unsigned short nPermission = 0;
    INT nPos = 1;
    INT nLast  = 9;

    TRACE("\n");
    if ((*lpszPermission != 'd') && (*lpszPermission != '-') && (*lpszPermission != 'l'))
    {
        bSuccess = FALSE;
        return bSuccess;
    }

    lpfp->bIsDirectory = (*lpszPermission == 'd');
    do
    {
        switch (nPos)
        {
            case 1:
                nPermission |= (*(lpszPermission+1) == 'r' ? 1 : 0) << 8;
                break;
            case 2:
                nPermission |= (*(lpszPermission+2) == 'w' ? 1 : 0) << 7;
                break;
            case 3:
                nPermission |= (*(lpszPermission+3) == 'x' ? 1 : 0) << 6;
                break;
            case 4:
                nPermission |= (*(lpszPermission+4) == 'r' ? 1 : 0) << 5;
                break;
            case 5:
                nPermission |= (*(lpszPermission+5) == 'w' ? 1 : 0) << 4;
                break;
            case 6:
                nPermission |= (*(lpszPermission+6) == 'x' ? 1 : 0) << 3;
                break;
            case 7:
                nPermission |= (*(lpszPermission+7) == 'r' ? 1 : 0) << 2;
                break;
            case 8:
                nPermission |= (*(lpszPermission+8) == 'w' ? 1 : 0) << 1;
                break;
            case 9:
                nPermission |= (*(lpszPermission+9) == 'x' ? 1 : 0);
                break;
        }
        nPos++;
    }while (nPos <= nLast);

    lpfp->permissions = nPermission;
    return bSuccess;
}