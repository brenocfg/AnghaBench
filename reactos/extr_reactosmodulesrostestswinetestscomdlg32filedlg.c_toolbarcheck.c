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
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GW_HWNDNEXT ; 
 int /*<<< orphan*/  GetClassNameA (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * GetWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_ADDSTRINGA ; 
 int /*<<< orphan*/  TB_GETTEXTROWS ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void toolbarcheck( HWND hDlg)
{
    /* test toolbar properties */
    /* bug #10532 */
    int maxtextrows;
    HWND ctrl;
    DWORD ret;
    char classname[20];

    for( ctrl = GetWindow( hDlg, GW_CHILD);
            ctrl ; ctrl = GetWindow( ctrl, GW_HWNDNEXT)) {
        GetClassNameA( ctrl, classname, 10);
        classname[7] = '\0';
        if( !strcmp( classname, "Toolbar")) break;
    }
    ok( ctrl != NULL, "could not get the toolbar control\n");
    ret = SendMessageA( ctrl, TB_ADDSTRINGA, 0, (LPARAM)"winetestwinetest\0\0");
    ok( ret == 0, "addstring returned %d (expected 0)\n", ret);
    maxtextrows = SendMessageA( ctrl, TB_GETTEXTROWS, 0, 0);
    ok( maxtextrows == 0 || broken(maxtextrows == 1),  /* Win2k and below */
        "Get(Max)TextRows returned %d (expected 0)\n", maxtextrows);
}