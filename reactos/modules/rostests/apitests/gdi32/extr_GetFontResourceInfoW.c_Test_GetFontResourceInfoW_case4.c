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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  GFRI_ENTRY ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int GetFontResourceInfoW (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 scalar_t__ lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_int (int,int) ; 

__attribute__((used)) static void
Test_GetFontResourceInfoW_case4(LPCWSTR pszFilePath, const GFRI_ENTRY *Entry)
{
    BOOL Ret;
    DWORD Size, Case = 4;
    WCHAR Data[MAX_PATH];

    /* data NULL, size zero */
    Size = 0;
    Ret = GetFontResourceInfoW(pszFilePath, &Size, NULL, Case);
    ok_int(Ret, 1);
    ok_int(Size, (lstrlenW(pszFilePath) + 1) * sizeof(WCHAR));

    /* data NULL, size non-zero */
    Size = MAX_PATH;
    Ret = GetFontResourceInfoW(pszFilePath, &Size, NULL, Case);
    ok_int(Ret, 0);
    ok_int(Size, MAX_PATH);

    /* size zero */
    Size = 0;
    Ret = GetFontResourceInfoW(pszFilePath, &Size, Data, Case);
    ok_int(Ret, 1);
    ok_int(Size, (lstrlenW(pszFilePath) + 1) * sizeof(WCHAR));

    /* size non-zero */
    Size = MAX_PATH;
    Ret = GetFontResourceInfoW(pszFilePath, &Size, Data, Case);
    ok_int(Ret, 1);
    ok_int(Size, (lstrlenW(pszFilePath) + 1) * sizeof(WCHAR));
    ok(lstrcmpiW(pszFilePath, Data) == 0, "data mismatched: \"%S\"\n", Data);
}