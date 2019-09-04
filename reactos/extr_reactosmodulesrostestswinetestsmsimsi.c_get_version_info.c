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
struct TYPE_2__ {int /*<<< orphan*/  dwFileVersionLS; int /*<<< orphan*/  dwFileVersionMS; } ;
typedef  TYPE_1__ VS_FIXEDFILEINFO ;
typedef  int USHORT ;
typedef  void* LPVOID ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/ * LPDWORD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetFileVersionInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFileVersionInfoSizeA (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  VerQueryValueA (int /*<<< orphan*/ ,char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrlenA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void get_version_info(LPSTR path, LPSTR *vercheck, LPDWORD verchecksz,
                             LPSTR *langcheck, LPDWORD langchecksz)
{
    LPSTR version;
    VS_FIXEDFILEINFO *ffi;
    DWORD size = GetFileVersionInfoSizeA(path, NULL);
    USHORT *lang;

    version = HeapAlloc(GetProcessHeap(), 0, size);
    GetFileVersionInfoA(path, 0, size, version);

    VerQueryValueA(version, "\\", (LPVOID *)&ffi, &size);
    *vercheck = HeapAlloc(GetProcessHeap(), 0, MAX_PATH);
    sprintf(*vercheck, "%d.%d.%d.%d", HIWORD(ffi->dwFileVersionMS),
            LOWORD(ffi->dwFileVersionMS), HIWORD(ffi->dwFileVersionLS),
            LOWORD(ffi->dwFileVersionLS));
    *verchecksz = lstrlenA(*vercheck);

    VerQueryValueA(version, "\\VarFileInfo\\Translation", (void **)&lang, &size);
    *langcheck = HeapAlloc(GetProcessHeap(), 0, MAX_PATH);
    sprintf(*langcheck, "%d", *lang);
    *langchecksz = lstrlenA(*langcheck);

    HeapFree(GetProcessHeap(), 0, version);
}