#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int /*<<< orphan*/  db; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIQUERY ;
typedef  TYPE_2__ MSIPACKAGE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_IterateRecords (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ MSI_OpenQuery (int /*<<< orphan*/ ,TYPE_1__**,char const*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  iterate_appsearch ; 
 scalar_t__ msi_action_is_unique (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_register_unique_action (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szAppSearch ; 

UINT ACTION_AppSearch(MSIPACKAGE *package)
{
    static const WCHAR query[] =  {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
        'A','p','p','S','e','a','r','c','h',0};
    MSIQUERY *view;
    UINT r;

    if (msi_action_is_unique(package, szAppSearch))
    {
        TRACE("Skipping AppSearch action: already done in UI sequence\n");
        return ERROR_SUCCESS;
    }
    else
        msi_register_unique_action(package, szAppSearch);

    r = MSI_OpenQuery( package->db, &view, query );
    if (r != ERROR_SUCCESS)
        return ERROR_SUCCESS;

    r = MSI_IterateRecords( view, NULL, iterate_appsearch, package );
    msiobj_release( &view->hdr );
    return r;
}