#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {scalar_t__ Preinstalled; int /*<<< orphan*/  File; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_1__ GFRI_ENTRY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddFontResourceW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetFileAttributesW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSystemFontPath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTempFileNameW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTempPathW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockResource (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 scalar_t__ RT_RCDATA ; 
 int /*<<< orphan*/  RemoveFontResourceW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SizeofResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Test_GetFontResourceInfoW_case0 (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  Test_GetFontResourceInfoW_case1 (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  Test_GetFontResourceInfoW_case2 (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  Test_GetFontResourceInfoW_case3 (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  Test_GetFontResourceInfoW_case4 (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  Test_GetFontResourceInfoW_case5 (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
DoEntry(const GFRI_ENTRY *Entry)
{
    WCHAR szPath[MAX_PATH], szTempPath[MAX_PATH];
    BOOL Installed = FALSE;

    if (Entry->Preinstalled)
    {
        GetSystemFontPath(szPath, Entry->File);
        printf("GetSystemFontPath: %S\n", szPath);
        if (GetFileAttributesW(szPath) == INVALID_FILE_ATTRIBUTES)
        {
            skip("Font file \"%S\" was not found\n", szPath);
            return;
        }
    }
    else
    {
        /* load font data from resource */
        HANDLE hFile;
        HMODULE hMod = GetModuleHandleW(NULL);
        HRSRC hRsrc = FindResourceW(hMod, Entry->File, (LPCWSTR)RT_RCDATA);
        HGLOBAL hGlobal = LoadResource(hMod, hRsrc);
        DWORD Size = SizeofResource(hMod, hRsrc);
        LPVOID pFont = LockResource(hGlobal);

        /* get temporary file name */
        GetTempPathW(_countof(szTempPath), szTempPath);
        GetTempFileNameW(szTempPath, L"FNT", 0, szPath);
        printf("GetTempFileNameW: %S\n", szPath);

        /* write to file */
        hFile = CreateFileW(szPath, GENERIC_WRITE, FILE_SHARE_READ, NULL,
                            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        WriteFile(hFile, pFont, Size, &Size, NULL);
        CloseHandle(hFile);

        /* check existence */
        if (GetFileAttributesW(szPath) == INVALID_FILE_ATTRIBUTES)
        {
            skip("Font file \"%S\" was not stored\n", szPath);
            return;
        }

        /* install */
        Installed = !!AddFontResourceW(szPath);
        if (!Installed)
        {
            skip("Font file \"%S\" was not installed\n", szPath);
            RemoveFontResourceW(szPath);
            DeleteFileW(szPath);
            return;
        }
    }

    Test_GetFontResourceInfoW_case0(szPath, Entry);
    Test_GetFontResourceInfoW_case1(szPath, Entry);
    Test_GetFontResourceInfoW_case2(szPath, Entry);
    Test_GetFontResourceInfoW_case3(szPath, Entry);
    Test_GetFontResourceInfoW_case4(szPath, Entry);
    Test_GetFontResourceInfoW_case5(szPath, Entry);

    if (!Entry->Preinstalled)
    {
        if (Installed)
        {
            RemoveFontResourceW(szPath);
            DeleteFileW(szPath);
        }
    }
}