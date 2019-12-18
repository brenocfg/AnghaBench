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
typedef  int WCHAR ;
struct TYPE_3__ {char* FontInfo; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ GFRI_ENTRY ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (int*,char*,int) ; 
 int GetFontResourceInfoW (int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  SzFromMultiSz (int*) ; 
 scalar_t__ lstrcmpiW (int*,char*) ; 
 int lstrlenW (int*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_int (int,int) ; 
 int /*<<< orphan*/  printf (char*,int,char) ; 

__attribute__((used)) static void
Test_GetFontResourceInfoW_case1(LPCWSTR pszFilePath, const GFRI_ENTRY *Entry)
{
    BOOL Ret;
    DWORD Size, Case = 1;
    static WCHAR Data[1024 / sizeof(WCHAR)];

    /* data NULL, size zero */
    Size = 0;
    Ret = GetFontResourceInfoW(pszFilePath, &Size, NULL, Case);
    ok_int(Ret, 1);
    /* FIXME: What's the result of Size? */
    ok(Size != 0, "Size expected non-zero but zero\n");

    /* data NULL, size non-zero */
    Size = 1024;
    Ret = GetFontResourceInfoW(pszFilePath, &Size, NULL, Case);
    ok_int(Ret, 0);
    ok_int(Size, 1024);

    /* size zero */
    Size = 0;
    CopyMemory(Data, L"ABC\0", sizeof(L"ABC\0"));
    Ret = GetFontResourceInfoW(pszFilePath, &Size, Data, Case);
    ok_int(Ret, 1);
    /* FIXME: What's the result of Size? */
    ok(Size != 0, "Size expected non-zero but zero\n");
    ok(lstrcmpiW(Data, L"ABC") == 0, "data mismatched: \"%S\"\n", Data);

    /* size non-zero */
    Size = 1024;
    CopyMemory(Data, L"ABC\0", sizeof(L"ABC\0"));
    Ret = GetFontResourceInfoW(pszFilePath, &Size, Data, Case);
    ok_int(Ret, 1);
    /* FIXME: What's the result of Size? */
    ok(Size != 0, "Size expected non-zero but zero\n");

    SzFromMultiSz(Data);
    ok(lstrcmpiW(Data, Entry->FontInfo) == 0, "data mismatched: \"%S\" and \"%S\"\n",
       Data, Entry->FontInfo);
#if 0
    if (lstrcmpiW(Data, Entry->FontInfo) != 0)
    {
        int i, len = lstrlenW(Data) + 1;
        for (i = 0; i < len; ++i)
        {
            printf("0x%04X <=> 0x%04X\n", Data[i], Entry->FontInfo[i]);
        }
    }
#endif
}