#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int FontCount; int** FaceNames; } ;
struct TYPE_6__ {int* lfFaceName; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ LOGFONTW ;
typedef  TYPE_2__ GFRI_ENTRY ;
typedef  int /*<<< orphan*/  Data ;
typedef  size_t DWORD ;
typedef  size_t BOOL ;

/* Variables and functions */
 size_t GetFontResourceInfoW (int /*<<< orphan*/ ,size_t*,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 scalar_t__ lstrcmpiW (int*,int*) ; 
 int lstrlenW (int*) ; 
 int /*<<< orphan*/  ok (int,char*,int,int*,int*) ; 
 int /*<<< orphan*/  ok_int (size_t,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void
Test_GetFontResourceInfoW_case2(LPCWSTR pszFilePath, const GFRI_ENTRY *Entry)
{
    BOOL Ret;
    DWORD i, Size, Case = 2;
    static LOGFONTW Data[100];

    /* data NULL, size zero */
    Size = 0;
    Ret = GetFontResourceInfoW(pszFilePath, &Size, NULL, Case);
    ok_int(Ret, 1);
    ok_int(Size, Entry->FontCount * sizeof(LOGFONTW));

    /* data NULL, size non-zero */
    Size = 1024;
    Ret = GetFontResourceInfoW(pszFilePath, &Size, NULL, Case);
    ok_int(Ret, 0);
    ok_int(Size, 1024);

    /* size zero */
    Size = 0;
    ZeroMemory(Data, sizeof(Data));
    Ret = GetFontResourceInfoW(pszFilePath, &Size, Data, Case);
    ok_int(Ret, 1);
    ok_int(Size, Entry->FontCount * sizeof(LOGFONTW));

    /* size non-zero */
    Size = sizeof(Data);
    ZeroMemory(Data, sizeof(Data));
    Ret = GetFontResourceInfoW(pszFilePath, &Size, Data, Case);
    ok_int(Ret, 1);
    ok_int(Size, Entry->FontCount * sizeof(LOGFONTW));
    for (i = 0; i < Entry->FontCount; ++i)
    {
        ok(lstrcmpiW(Data[i].lfFaceName, Entry->FaceNames[i]) == 0,
            "face name #%d mismatched: \"%S\" and \"%S\"\n", (int)i, Data[i].lfFaceName, Entry->FaceNames[i]);
#if 0
        if (lstrcmpiW(Data[i].lfFaceName, Entry->FaceNames[i]) != 0)
        {
            int k, len = lstrlenW(Data[i].lfFaceName);
            for (k = 0; k < len; ++k)
            {
                printf("0x%04X <=> 0x%04X\n", Entry->FaceNames[i][k], Data[i].lfFaceName[k]);
            }
        }
#endif
    }
}