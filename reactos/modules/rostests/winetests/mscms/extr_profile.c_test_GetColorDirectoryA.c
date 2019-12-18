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
typedef  int /*<<< orphan*/  buffer ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pGetColorDirectoryA (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static void test_GetColorDirectoryA(void)
{
    BOOL ret;
    DWORD size;
    char buffer[MAX_PATH];

    /* Parameter checks */

    ret = pGetColorDirectoryA( NULL, NULL, NULL );
    ok( !ret, "GetColorDirectoryA() succeeded (%d)\n", GetLastError() );

    size = 0;

    ret = pGetColorDirectoryA( NULL, NULL, &size );
    ok( !ret && size > 0, "GetColorDirectoryA() succeeded (%d)\n", GetLastError() );

    size = 0;

    ret = pGetColorDirectoryA( NULL, buffer, &size );
    ok( !ret && size > 0, "GetColorDirectoryA() succeeded (%d)\n", GetLastError() );

    size = 1;

    ret = pGetColorDirectoryA( NULL, buffer, &size );
    ok( !ret && size > 0, "GetColorDirectoryA() succeeded (%d)\n", GetLastError() );

    /* Functional checks */

    size = sizeof(buffer);

    ret = pGetColorDirectoryA( NULL, buffer, &size );
    ok( ret && size > 0, "GetColorDirectoryA() failed (%d)\n", GetLastError() );
}