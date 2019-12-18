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
struct TYPE_3__ {int member_0; unsigned int dwMinorVersion; unsigned int dwMajorVersion; int dwBuildNumber; unsigned int dwPlatformId; } ;
typedef  TYPE_1__ OSVERSIONINFOA ;
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetVersionExA (TYPE_1__*) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_initvar( HMODULE hmsvcrt )
{
    OSVERSIONINFOA osvi = { sizeof(OSVERSIONINFOA) };
    int *pp_winver   = (int*)GetProcAddress(hmsvcrt, "_winver");
    int *pp_winmajor = (int*)GetProcAddress(hmsvcrt, "_winmajor");
    int *pp_winminor = (int*)GetProcAddress(hmsvcrt, "_winminor");
    int *pp_osver    = (int*)GetProcAddress(hmsvcrt, "_osver");
    int *pp_osplatform = (int*)GetProcAddress(hmsvcrt, "_osplatform");
    unsigned int winver, winmajor, winminor, osver, osplatform;

    if( !( pp_winmajor && pp_winminor && pp_winver)) {
        win_skip("_winver variables are not available\n");
        return;
    }
    winver = *pp_winver;
    winminor = *pp_winminor;
    winmajor = *pp_winmajor;
    GetVersionExA( &osvi);
    ok( winminor == osvi.dwMinorVersion, "Wrong value for _winminor %02x expected %02x\n",
            winminor, osvi.dwMinorVersion);
    ok( winmajor == osvi.dwMajorVersion, "Wrong value for _winmajor %02x expected %02x\n",
            winmajor, osvi.dwMajorVersion);
    ok( winver == ((osvi.dwMajorVersion << 8) | osvi.dwMinorVersion),
            "Wrong value for _winver %02x expected %02x\n",
            winver, ((osvi.dwMajorVersion << 8) | osvi.dwMinorVersion));
    if( !pp_osver || !pp_osplatform ) {
        win_skip("_osver variables are not available\n");
        return;
    }
    osver = *pp_osver;
    osplatform = *pp_osplatform;
    ok( osver == (osvi.dwBuildNumber & 0xffff) ||
            ((osvi.dwBuildNumber >> 24) == osvi.dwMajorVersion &&
                 ((osvi.dwBuildNumber >> 16) & 0xff) == osvi.dwMinorVersion), /* 95/98/ME */
            "Wrong value for _osver %04x expected %04x\n",
            osver, osvi.dwBuildNumber);
    ok(osplatform == osvi.dwPlatformId,
            "Wrong value for _osplatform %x expected %x\n",
            osplatform, osvi.dwPlatformId);
}