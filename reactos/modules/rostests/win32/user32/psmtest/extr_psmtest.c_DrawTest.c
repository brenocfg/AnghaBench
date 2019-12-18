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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int LPK ; 
 int /*<<< orphan*/  LpkPSMTextOut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCchPrintfW (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TextOutW (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 
 int USERLPK ; 
 int /*<<< orphan*/  UserLpkPSMTextOut (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DrawTest(HDC hdc, int ypos, LPCWSTR str, DWORD dwFlags, int testtype)
{
    WCHAR Result[100];
    INT ret = 0;

    if (testtype == LPK)
    {
        ret = LpkPSMTextOut(hdc, 0, ypos, str, (!str) ? 10 : wcslen(str), dwFlags);
        StringCchPrintfW(Result, 100, L"Return Value = %d", ret);
        TextOutW(hdc, 200, ypos, Result, wcslen(Result));
    }
    else if (testtype == USERLPK)
    {
        ret = UserLpkPSMTextOut(hdc, 400, ypos, str, wcslen(str), dwFlags);
        StringCchPrintfW(Result, 100, L"Return Value = %d", ret);
        TextOutW(hdc, 600, ypos, Result, wcslen(Result));
    }

}