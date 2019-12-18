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
typedef  int /*<<< orphan*/  ato ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int cbSize; int /*<<< orphan*/  iTimeOutMSec; } ;
typedef  int DWORD ;
typedef  TYPE_1__ ACCESSTIMEOUT ;

/* Variables and functions */
 int /*<<< orphan*/  NtUserSystemParametersInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QueryUserRegValueW (char*,char*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPI_GETACCESSTIMEOUT ; 
 int /*<<< orphan*/  SPI_SETACCESSTIMEOUT ; 

void
Test_NtUserSystemParametersInfo_fWinIni(void)
{
    ACCESSTIMEOUT ato;
//  UINT uFocusBorderHeight;
    WCHAR Buffer[6];
    DWORD cbSize;

    ato.cbSize = sizeof(ato);
    NtUserSystemParametersInfo(SPI_GETACCESSTIMEOUT, 0, &ato, 0);
    ato.iTimeOutMSec++;
    NtUserSystemParametersInfo(SPI_SETACCESSTIMEOUT, 0, &ato, 0);
    ato.iTimeOutMSec--;

//  NtUserSystemParametersInfo(SPI_GETFOCUSBORDERHEIGHT, 0, &uFocusBorderHeight, 0);
//  NtUserSystemParametersInfo(SPI_SETFOCUSBORDERHEIGHT, 0, &uFocusBorderHeight, SPIF_UPDATEINIFILE);

    NtUserSystemParametersInfo(SPI_SETACCESSTIMEOUT, 0, &ato, 0);

    cbSize = 6;
    QueryUserRegValueW(L"Control Panel\\Accessibility\\TimeOut", L"TimeToWait", &Buffer, &cbSize, NULL);

}