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
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * BeginUpdateResourceA (int /*<<< orphan*/ ,int) ; 
 int EndUpdateResourceA (int /*<<< orphan*/ *,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  MAKEINTRESOURCEA (int) ; 
 int TRUE ; 
 int UpdateResourceA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void update_resources_version( void )
{
    HANDLE res = NULL;
    BOOL r;
    char foo[] = "red and white";

    res = BeginUpdateResourceA( filename, TRUE );
    ok( res != NULL, "BeginUpdateResource failed\n");

    if (0)  /* this causes subsequent tests to fail on Vista */
    {
        r = UpdateResourceA( res,
                            MAKEINTRESOURCEA(0x1230),
                            MAKEINTRESOURCEA(0x4567),
                            0xabcd,
                            NULL, 0 );
        ok( r == FALSE, "UpdateResource failed\n");
    }

    r = UpdateResourceA( res,
                        MAKEINTRESOURCEA(0x1230),
                        MAKEINTRESOURCEA(0x4567),
                        0xabcd,
                        foo, sizeof foo );
    ok( r == TRUE, "UpdateResource failed: %d\n", GetLastError());

    r = EndUpdateResourceA( res, FALSE );
    ok( r, "EndUpdateResource failed: %d\n", GetLastError());
}