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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 void* GetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTempFileNameW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTempPathW (int,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL ExtractTTFFile(LPCWSTR FontName, LPWSTR TempFile)
{
    WCHAR TempPath[MAX_PATH];
    HANDLE hFile;
    void *Data;
    DWORD Size;
    BOOL ret;

    Data = GetResource(FontName, &Size);
    if (!Data) return FALSE;

    GetTempPathW(MAX_PATH, TempPath);
    GetTempFileNameW(TempPath, L"ttf", 0, TempFile);

    hFile = CreateFileW(TempFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE) return FALSE;

    ret = WriteFile(hFile, Data, Size, &Size, NULL);

    CloseHandle(hFile);
    return ret;
}