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
struct TYPE_3__ {int dwOSVersionInfoSize; int /*<<< orphan*/  dwMajorVersion; int /*<<< orphan*/  dwMinorVersion; } ;
typedef  TYPE_1__ OSVERSIONINFOW ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetProcessVersion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetVersionExW (TYPE_1__*) ; 
 scalar_t__ MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD get_app_version(void)
{
    static DWORD version;
    if (!version)
    {
        DWORD dwEmulatedVersion;
        OSVERSIONINFOW info;
        DWORD dwProcVersion = GetProcessVersion(0);

	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
        GetVersionExW( &info );
        dwEmulatedVersion = MAKELONG( info.dwMinorVersion, info.dwMajorVersion );
        /* FIXME: this may not be 100% correct; see discussion on the
         * wine developer list in Nov 1999 */
        version = dwProcVersion < dwEmulatedVersion ? dwProcVersion : dwEmulatedVersion;
    }
    return version;
}