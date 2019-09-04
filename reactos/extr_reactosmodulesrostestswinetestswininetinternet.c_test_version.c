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
typedef  int /*<<< orphan*/  version ;
struct TYPE_3__ {int dwMajorVersion; int dwMinorVersion; } ;
typedef  TYPE_1__ INTERNET_VERSION_INFO ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int GetLastError () ; 
 int /*<<< orphan*/  INTERNET_OPTION_VERSION ; 
 int InternetQueryOptionA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_version(void)
{
    INTERNET_VERSION_INFO version;
    DWORD size;
    BOOL res;

    size = sizeof(version);
    res = InternetQueryOptionA(NULL, INTERNET_OPTION_VERSION, &version, &size);
    ok(res, "Could not get version: %u\n", GetLastError());
    ok(version.dwMajorVersion == 1, "dwMajorVersion=%d, expected 1\n", version.dwMajorVersion);
    ok(version.dwMinorVersion == 2, "dwMinorVersion=%d, expected 2\n", version.dwMinorVersion);
}