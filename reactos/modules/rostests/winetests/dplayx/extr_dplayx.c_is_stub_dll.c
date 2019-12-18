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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ GetFileVersionInfoA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetFileVersionInfoSizeA (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 scalar_t__ VerQueryValueA (char*,char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static BOOL is_stub_dll(const char *filename)
{
    DWORD size, ver;
    BOOL isstub = FALSE;
    char *p, *data;

    size = GetFileVersionInfoSizeA(filename, &ver);
    if (!size) return FALSE;

    data = HeapAlloc(GetProcessHeap(), 0, size);
    if (!data) return FALSE;

    if (GetFileVersionInfoA(filename, ver, size, data))
    {
        char buf[256];

        sprintf(buf, "\\StringFileInfo\\%04x%04x\\OriginalFilename", MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), 1200);
        if (VerQueryValueA(data, buf, (void**)&p, &size))
            isstub = !lstrcmpiA("wcodstub.dll", p);
    }
    HeapFree(GetProcessHeap(), 0, data);

    return isstub;
}