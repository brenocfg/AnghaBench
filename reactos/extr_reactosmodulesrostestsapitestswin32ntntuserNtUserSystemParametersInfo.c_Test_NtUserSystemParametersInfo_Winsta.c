#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWINSTA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowStation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessWindowStation () ; 
 int /*<<< orphan*/  READ_CONTROL ; 
 int /*<<< orphan*/  SPI_GETBEEP ; 
 int /*<<< orphan*/  SPI_GETBORDER ; 
 int /*<<< orphan*/  SPI_GETKEYBOARDCUES ; 
 int /*<<< orphan*/  SPI_GETKEYBOARDSPEED ; 
 int /*<<< orphan*/  SPI_GETMOUSE ; 
 int /*<<< orphan*/  SPI_GETSCREENSAVETIMEOUT ; 
 int /*<<< orphan*/  SPI_ICONHORIZONTALSPACING ; 
 int /*<<< orphan*/  SPI_SETBEEP ; 
 int /*<<< orphan*/  SPI_SETBORDER ; 
 int /*<<< orphan*/  SPI_SETKEYBOARDCUES ; 
 int /*<<< orphan*/  SPI_SETKEYBOARDSPEED ; 
 int /*<<< orphan*/  SPI_SETMOUSE ; 
 int /*<<< orphan*/  SPI_SETSCREENSAVETIMEOUT ; 
 int /*<<< orphan*/  SetProcessWindowStation (int /*<<< orphan*/ ) ; 
 scalar_t__ SystemParametersInfoA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST (int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
Test_NtUserSystemParametersInfo_Winsta(void)
{
    HWINSTA hwinsta, hwinstaOld;
    INT ai[20];
    BOOL bRet;
//    INT i;

    hwinstaOld = GetProcessWindowStation();
    hwinsta = CreateWindowStation(NULL, 0, READ_CONTROL, NULL);
    SetProcessWindowStation(hwinsta);
    printf("hwinstaOld=%p, hwinsta=%p\n", hwinstaOld, hwinsta);

#if 1 // currently Winsta stuff is broken in ros
    TEST(SystemParametersInfoA(SPI_GETBEEP, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_ACCESS_DENIED);
    TEST(SystemParametersInfoA(SPI_SETBEEP, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION);
    TEST(SystemParametersInfoA(SPI_GETMOUSE, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_ACCESS_DENIED);
    TEST(SystemParametersInfoA(SPI_SETMOUSE, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION);
    TEST(SystemParametersInfoA(SPI_GETBORDER, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_ACCESS_DENIED);
    TEST(SystemParametersInfoA(SPI_SETBORDER, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION);
    TEST(SystemParametersInfoA(SPI_GETKEYBOARDSPEED, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_ACCESS_DENIED);
    TEST(SystemParametersInfoA(SPI_SETKEYBOARDSPEED, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION);
    TEST(SystemParametersInfoA(SPI_ICONHORIZONTALSPACING, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_ACCESS_DENIED);
    TEST(SystemParametersInfoA(SPI_ICONHORIZONTALSPACING, 32, 0, 0) == 0);
    TEST(GetLastError() == ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION);
    TEST(SystemParametersInfoA(SPI_GETSCREENSAVETIMEOUT, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_ACCESS_DENIED);
    TEST(SystemParametersInfoA(SPI_SETSCREENSAVETIMEOUT, 0, ai, 0) == 0);
    TEST(GetLastError() == ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION);
    TEST(SystemParametersInfoA(SPI_GETKEYBOARDCUES, 0, &bRet, 0) == 0);
    TEST(GetLastError() == ERROR_ACCESS_DENIED);
    TEST(SystemParametersInfoA(SPI_SETKEYBOARDCUES, 0, (PVOID)1, 0) == 0);
    TEST(GetLastError() == ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION);
#endif

    SetProcessWindowStation(hwinstaOld);
}