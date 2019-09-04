#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
struct TYPE_7__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIQUERY ;
typedef  TYPE_2__ MSIPACKAGE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  ITERATE_Actions ; 
 scalar_t__ MSI_DatabaseOpenViewW (int /*<<< orphan*/ ,char const*,TYPE_1__**) ; 
 scalar_t__ MSI_IterateRecords (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT ACTION_ProcessUISequence(MSIPACKAGE *package)
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
        '`','I','n','s','t','a','l','l','U','I','S','e','q','u','e','n','c','e','`',' ',
        'W','H','E','R','E',' ','`','S','e','q','u','e','n','c','e','`',' ','>',' ','0',' ',
        'O','R','D','E','R',' ','B','Y',' ','`','S','e','q','u','e','n','c','e','`',0};
    MSIQUERY *view;
    UINT rc;

    rc = MSI_DatabaseOpenViewW(package->db, query, &view);
    if (rc == ERROR_SUCCESS)
    {
        TRACE("Running the actions\n"); 
        rc = MSI_IterateRecords(view, NULL, ITERATE_Actions, package);
        msiobj_release(&view->hdr);
    }
    return rc;
}