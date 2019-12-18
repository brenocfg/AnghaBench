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
struct TYPE_2__ {int dwFileVersionMS; int dwFileVersionLS; } ;
typedef  TYPE_1__ VS_FIXEDFILEINFO ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetFileVersionInfoA (char*,scalar_t__,scalar_t__,char*) ; 
 scalar_t__ GetFileVersionInfoSizeA (char*,scalar_t__*) ; 
 scalar_t__ VerQueryValueA (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static char * get_file_version(char * file_name)
{
    static char version[32];
    DWORD size;
    DWORD handle;

    size = GetFileVersionInfoSizeA(file_name, &handle);
    if (size) {
        char * data = xmalloc(size);
        if (data) {
            if (GetFileVersionInfoA(file_name, handle, size, data)) {
                static char backslash[] = "\\";
                VS_FIXEDFILEINFO *pFixedVersionInfo;
                UINT len;
                if (VerQueryValueA(data, backslash, (LPVOID *)&pFixedVersionInfo, &len)) {
                    sprintf(version, "%d.%d.%d.%d",
                            pFixedVersionInfo->dwFileVersionMS >> 16,
                            pFixedVersionInfo->dwFileVersionMS & 0xffff,
                            pFixedVersionInfo->dwFileVersionLS >> 16,
                            pFixedVersionInfo->dwFileVersionLS & 0xffff);
                } else
                    sprintf(version, "version not available");
            } else
                sprintf(version, "unknown");
            free(data);
        } else
            sprintf(version, "failed");
    } else
        sprintf(version, "version not available");

    return version;
}