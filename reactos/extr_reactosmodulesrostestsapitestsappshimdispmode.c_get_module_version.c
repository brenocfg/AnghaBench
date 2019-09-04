#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dwFileVersionMS; int /*<<< orphan*/  dwProductVersionMS; } ;
typedef  TYPE_1__ VS_FIXEDFILEINFO ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ HRSRC ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  HLOCAL ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FindResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeResource (int /*<<< orphan*/ ) ; 
 int HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LMEM_FIXED ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockResource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_VERSION ; 
 int SizeofResource (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VS_VERSION_INFO ; 
 scalar_t__ VerQueryValueW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DWORD get_module_version(HMODULE mod)
{
    DWORD dwVersion = 0;
    HRSRC hResInfo = FindResource(mod, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
    DWORD dwSize = SizeofResource(mod, hResInfo);
    if (hResInfo && dwSize)
    {
        VS_FIXEDFILEINFO *lpFfi;
        UINT uLen;

        HGLOBAL hResData = LoadResource(mod, hResInfo);
        LPVOID pRes = LockResource(hResData);
        HLOCAL pResCopy = LocalAlloc(LMEM_FIXED, dwSize);

        CopyMemory(pResCopy, pRes, dwSize);
        FreeResource(hResData);

        if (VerQueryValueW(pResCopy, L"\\", (LPVOID*)&lpFfi, &uLen))
        {
            dwVersion = (HIWORD(lpFfi->dwProductVersionMS) << 8) | LOWORD(lpFfi->dwProductVersionMS);
            if (!dwVersion)
                dwVersion = (HIWORD(lpFfi->dwFileVersionMS) << 8) | LOWORD(lpFfi->dwFileVersionMS);
        }

        LocalFree(pResCopy);
    }

    return dwVersion;
}