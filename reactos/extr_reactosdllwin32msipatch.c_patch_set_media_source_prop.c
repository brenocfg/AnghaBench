#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_12__ {int /*<<< orphan*/  db; } ;
struct TYPE_11__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_10__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIQUERY ;
typedef  TYPE_3__ MSIPACKAGE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_DatabaseOpenViewW (int /*<<< orphan*/ ,char const*,TYPE_2__**) ; 
 char* MSI_RecordGetString (TYPE_1__*,int) ; 
 scalar_t__ MSI_ViewExecute (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MSI_ViewFetch (TYPE_2__*,TYPE_1__**) ; 
 char* msi_dup_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 int /*<<< orphan*/  msi_set_property (int /*<<< orphan*/ ,char const*,char*,int) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szPatch ; 

__attribute__((used)) static UINT patch_set_media_source_prop( MSIPACKAGE *package )
{
    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','`','S','o','u','r','c','e','`',' ','F','R','O','M',' ',
        '`','M','e','d','i','a','`',' ','W','H','E','R','E',' ','`','S','o','u','r','c','e','`',' ',
        'I','S',' ','N','O','T',' ','N','U','L','L',0};
    MSIQUERY *view;
    MSIRECORD *rec;
    const WCHAR *property;
    WCHAR *patch;
    UINT r;

    r = MSI_DatabaseOpenViewW( package->db, query, &view );
    if (r != ERROR_SUCCESS)
        return r;

    r = MSI_ViewExecute( view, 0 );
    if (r != ERROR_SUCCESS)
        goto done;

    if (MSI_ViewFetch( view, &rec ) == ERROR_SUCCESS)
    {
        property = MSI_RecordGetString( rec, 1 );
        patch = msi_dup_property( package->db, szPatch );
        msi_set_property( package->db, property, patch, -1 );
        msi_free( patch );
        msiobj_release( &rec->hdr );
    }

done:
    msiobj_release( &view->hdr );
    return r;
}