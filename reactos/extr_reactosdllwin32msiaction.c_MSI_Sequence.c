#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  db; } ;
struct TYPE_8__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIQUERY ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  ITERATE_Actions ; 
 scalar_t__ MSI_IterateRecords (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ MSI_OpenQuery (int /*<<< orphan*/ ,TYPE_1__**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

UINT MSI_Sequence( MSIPACKAGE *package, LPCWSTR table )
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','`','%','s','`',
         ' ','W','H','E','R','E',' ','`','S','e','q','u','e','n','c','e','`',' ',
         '>',' ','0',' ','O','R','D','E','R',' ','B','Y',' ',
         '`','S','e','q','u','e','n','c','e','`',0};
    MSIQUERY *view;
    UINT r;

    TRACE("%p %s\n", package, debugstr_w(table));

    r = MSI_OpenQuery( package->db, &view, query, table );
    if (r == ERROR_SUCCESS)
    {
        r = MSI_IterateRecords( view, NULL, ITERATE_Actions, package );
        msiobj_release(&view->hdr);
    }
    return r;
}