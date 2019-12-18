#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * szKey; } ;
typedef  TYPE_1__ VS_VERSIONINFO ;
struct TYPE_5__ {void* dwProductVersionLS; void* dwProductVersionMS; void* dwFileVersionLS; void* dwFileVersionMS; } ;
typedef  TYPE_2__ VS_FIXEDFILEINFO ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  void* LONG ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BeginUpdateResourceA (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyFileA (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndUpdateResourceA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetFileVersionInfoA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetFileVersionInfoSizeA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetSystemDirectoryA (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 scalar_t__ MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 scalar_t__ RT_VERSION ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateResourceA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VS_VERSION_INFO ; 
 int /*<<< orphan*/  lstrcatA (int /*<<< orphan*/ *,char*) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 scalar_t__ roundpos (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL create_file_with_version(const CHAR *name, LONG ms, LONG ls)
{
    VS_VERSIONINFO *pVerInfo;
    VS_FIXEDFILEINFO *pFixedInfo;
    LPBYTE buffer, ofs;
    CHAR path[MAX_PATH];
    DWORD handle, size;
    HANDLE resource;
    BOOL ret = FALSE;

    GetSystemDirectoryA(path, MAX_PATH);
    /* Some dlls can't be updated on Vista/W2K8 */
    lstrcatA(path, "\\version.dll");

    CopyFileA(path, name, FALSE);

    size = GetFileVersionInfoSizeA(path, &handle);
    buffer = HeapAlloc(GetProcessHeap(), 0, size);

    GetFileVersionInfoA(path, 0, size, buffer);

    pVerInfo = (VS_VERSIONINFO *)buffer;
    ofs = (BYTE *)&pVerInfo->szKey[lstrlenW(pVerInfo->szKey) + 1];
    pFixedInfo = (VS_FIXEDFILEINFO *)roundpos(pVerInfo, ofs, 4);

    pFixedInfo->dwFileVersionMS = ms;
    pFixedInfo->dwFileVersionLS = ls;
    pFixedInfo->dwProductVersionMS = ms;
    pFixedInfo->dwProductVersionLS = ls;

    resource = BeginUpdateResourceA(name, FALSE);
    if (!resource)
        goto done;

    if (!UpdateResourceA(resource, (LPCSTR)RT_VERSION, (LPCSTR)MAKEINTRESOURCE(VS_VERSION_INFO),
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), buffer, size))
        goto done;

    if (!EndUpdateResourceA(resource, FALSE))
        goto done;

    ret = TRUE;

done:
    HeapFree(GetProcessHeap(), 0, buffer);
    return ret;
}