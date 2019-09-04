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
typedef  int /*<<< orphan*/  hviews ;
typedef  scalar_t__ UINT ;
typedef  int MSIHANDLE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int MY_NVIEWS ; 
 scalar_t__ MsiCloseHandle (int) ; 
 scalar_t__ MsiDatabaseOpenViewA (int,char*,int*) ; 
 int /*<<< orphan*/  MsiViewClose (int) ; 
 int create_db () ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_handle_limit(void)
{
    int i;
    MSIHANDLE hdb;
    MSIHANDLE hviews[MY_NVIEWS];
    UINT r;

    /* create an empty db */
    hdb = create_db();
    ok( hdb, "failed to create db\n");

    memset(hviews, 0, sizeof(hviews));

    for (i=0; i<MY_NVIEWS; i++) {
        static char szQueryBuf[256] = "SELECT * from `_Tables`";
        hviews[i] = 0xdeadbeeb;
        r = MsiDatabaseOpenViewA(hdb, szQueryBuf, &hviews[i]);
        if( r != ERROR_SUCCESS || hviews[i] == 0xdeadbeeb || 
            hviews[i] == 0 || (i && (hviews[i] == hviews[i-1])))
            break;
    }

    ok( i == MY_NVIEWS, "problem opening views\n");

    for (i=0; i<MY_NVIEWS; i++) {
        if (hviews[i] != 0 && hviews[i] != 0xdeadbeeb) {
            MsiViewClose(hviews[i]);
            r = MsiCloseHandle(hviews[i]);
            if (r != ERROR_SUCCESS)
                break;
        }
    }

    ok( i == MY_NVIEWS, "problem closing views\n");

    r = MsiCloseHandle(hdb);
    ok( r == ERROR_SUCCESS, "failed to close database\n");
}