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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pGetColorDirectoryW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void test_GetColorDirectoryW(void)
{
    BOOL ret;
    DWORD size;
    WCHAR buffer[MAX_PATH];

    /* Parameter checks */

    /* This one crashes win2k
    
    ret = pGetColorDirectoryW( NULL, NULL, NULL );
    ok( !ret, "GetColorDirectoryW() succeeded (%d)\n", GetLastError() );

     */

    size = 0;

    ret = pGetColorDirectoryW( NULL, NULL, &size );
    ok( !ret && size > 0, "GetColorDirectoryW() succeeded (%d)\n", GetLastError() );

    size = 0;

    ret = pGetColorDirectoryW( NULL, buffer, &size );
    ok( !ret && size > 0, "GetColorDirectoryW() succeeded (%d)\n", GetLastError() );

    size = 1;

    ret = pGetColorDirectoryW( NULL, buffer, &size );
    ok( !ret && size > 0, "GetColorDirectoryW() succeeded (%d)\n", GetLastError() );

    /* Functional checks */

    size = sizeof(buffer);

    ret = pGetColorDirectoryW( NULL, buffer, &size );
    ok( ret && size > 0, "GetColorDirectoryW() failed (%d)\n", GetLastError() );
}