#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIQUERY ;
typedef  int /*<<< orphan*/  MSIDATABASE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 TYPE_1__* MSI_CreateRecord (int) ; 
 scalar_t__ MSI_DatabaseOpenViewW (int /*<<< orphan*/ *,char const*,TYPE_2__**) ; 
 int /*<<< orphan*/  MSI_RecordCopyField (TYPE_1__*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSI_ViewClose (TYPE_2__*) ; 
 scalar_t__ MSI_ViewExecute (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ MSI_ViewFetch (TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

UINT msi_clone_properties( MSIDATABASE *db )
{
    static const WCHAR query_select[] = {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
        '`','P','r','o','p','e','r','t','y','`',0};
    static const WCHAR query_insert[] = {
        'I','N','S','E','R','T',' ','I','N','T','O',' ',
        '`','_','P','r','o','p','e','r','t','y','`',' ',
        '(','`','_','P','r','o','p','e','r','t','y','`',',','`','V','a','l','u','e','`',')',' ',
        'V','A','L','U','E','S',' ','(','?',',','?',')',0};
    static const WCHAR query_update[] = {
        'U','P','D','A','T','E',' ','`','_','P','r','o','p','e','r','t','y','`',' ',
        'S','E','T',' ','`','V','a','l','u','e','`',' ','=',' ','?',' ',
        'W','H','E','R','E',' ','`','_','P','r','o','p','e','r','t','y','`',' ','=',' ','?',0};
    MSIQUERY *view_select;
    UINT rc;

    rc = MSI_DatabaseOpenViewW( db, query_select, &view_select );
    if (rc != ERROR_SUCCESS)
        return rc;

    rc = MSI_ViewExecute( view_select, 0 );
    if (rc != ERROR_SUCCESS)
    {
        MSI_ViewClose( view_select );
        msiobj_release( &view_select->hdr );
        return rc;
    }

    while (1)
    {
        MSIQUERY *view_insert, *view_update;
        MSIRECORD *rec_select;

        rc = MSI_ViewFetch( view_select, &rec_select );
        if (rc != ERROR_SUCCESS)
            break;

        rc = MSI_DatabaseOpenViewW( db, query_insert, &view_insert );
        if (rc != ERROR_SUCCESS)
        {
            msiobj_release( &rec_select->hdr );
            continue;
        }

        rc = MSI_ViewExecute( view_insert, rec_select );
        MSI_ViewClose( view_insert );
        msiobj_release( &view_insert->hdr );
        if (rc != ERROR_SUCCESS)
        {
            MSIRECORD *rec_update;

            TRACE("insert failed, trying update\n");

            rc = MSI_DatabaseOpenViewW( db, query_update, &view_update );
            if (rc != ERROR_SUCCESS)
            {
                WARN("open view failed %u\n", rc);
                msiobj_release( &rec_select->hdr );
                continue;
            }

            rec_update = MSI_CreateRecord( 2 );
            MSI_RecordCopyField( rec_select, 1, rec_update, 2 );
            MSI_RecordCopyField( rec_select, 2, rec_update, 1 );
            rc = MSI_ViewExecute( view_update, rec_update );
            if (rc != ERROR_SUCCESS)
                WARN("update failed %u\n", rc);

            MSI_ViewClose( view_update );
            msiobj_release( &view_update->hdr );
            msiobj_release( &rec_update->hdr );
        }

        msiobj_release( &rec_select->hdr );
    }

    MSI_ViewClose( view_select );
    msiobj_release( &view_select->hdr );
    return rc;
}