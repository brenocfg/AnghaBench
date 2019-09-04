#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_DATATYPE_MISMATCH ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_DatabaseGetPrimaryKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ MSI_RecordGetFieldCount (TYPE_1__*) ; 
 int /*<<< orphan*/  MSI_RecordGetString (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT merge_verify_primary_keys(MSIDATABASE *db, MSIDATABASE *mergedb,
                                      LPCWSTR table)
{
    MSIRECORD *dbrec, *mergerec = NULL;
    UINT r, i, count;

    r = MSI_DatabaseGetPrimaryKeys(db, table, &dbrec);
    if (r != ERROR_SUCCESS)
        return r;

    r = MSI_DatabaseGetPrimaryKeys(mergedb, table, &mergerec);
    if (r != ERROR_SUCCESS)
        goto done;

    count = MSI_RecordGetFieldCount(dbrec);
    if (count != MSI_RecordGetFieldCount(mergerec))
    {
        r = ERROR_DATATYPE_MISMATCH;
        goto done;
    }

    for (i = 1; i <= count; i++)
    {
        if (strcmpW( MSI_RecordGetString( dbrec, i ), MSI_RecordGetString( mergerec, i ) ))
        {
            r = ERROR_DATATYPE_MISMATCH;
            goto done;
        }
    }

done:
    msiobj_release(&dbrec->hdr);
    msiobj_release(&mergerec->hdr);

    return r;
}