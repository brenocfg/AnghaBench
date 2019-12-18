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

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetCurrentDirectoryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SetCurrentDirectoryA(void)
{
    SetLastError(0);
    ok( !SetCurrentDirectoryA( "\\some_dummy_dir" ), "SetCurrentDirectoryA succeeded\n" );
    ok( GetLastError() == ERROR_FILE_NOT_FOUND, "wrong error %d\n", GetLastError() );
    ok( !SetCurrentDirectoryA( "\\some_dummy\\subdir" ), "SetCurrentDirectoryA succeeded\n" );
    ok( GetLastError() == ERROR_PATH_NOT_FOUND, "wrong error %d\n", GetLastError() );
}