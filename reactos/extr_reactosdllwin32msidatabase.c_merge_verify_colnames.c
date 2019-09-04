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
typedef  int /*<<< orphan*/  MSIQUERY ;

/* Variables and functions */
 scalar_t__ ERROR_DATATYPE_MISMATCH ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSICOLINFO_NAMES ; 
 int /*<<< orphan*/  MSICOLINFO_TYPES ; 
 scalar_t__ MSI_RecordGetFieldCount (TYPE_1__*) ; 
 int /*<<< orphan*/  MSI_RecordGetString (TYPE_1__*,scalar_t__) ; 
 scalar_t__ MSI_ViewGetColumnInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  merge_type_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT merge_verify_colnames(MSIQUERY *dbview, MSIQUERY *mergeview)
{
    MSIRECORD *dbrec, *mergerec;
    UINT r, i, count;

    r = MSI_ViewGetColumnInfo(dbview, MSICOLINFO_NAMES, &dbrec);
    if (r != ERROR_SUCCESS)
        return r;

    r = MSI_ViewGetColumnInfo(mergeview, MSICOLINFO_NAMES, &mergerec);
    if (r != ERROR_SUCCESS)
    {
        msiobj_release(&dbrec->hdr);
        return r;
    }

    count = MSI_RecordGetFieldCount(dbrec);
    for (i = 1; i <= count; i++)
    {
        if (!MSI_RecordGetString(mergerec, i))
            break;

        if (strcmpW( MSI_RecordGetString( dbrec, i ), MSI_RecordGetString( mergerec, i ) ))
        {
            r = ERROR_DATATYPE_MISMATCH;
            goto done;
        }
    }

    msiobj_release(&dbrec->hdr);
    msiobj_release(&mergerec->hdr);
    dbrec = mergerec = NULL;

    r = MSI_ViewGetColumnInfo(dbview, MSICOLINFO_TYPES, &dbrec);
    if (r != ERROR_SUCCESS)
        return r;

    r = MSI_ViewGetColumnInfo(mergeview, MSICOLINFO_TYPES, &mergerec);
    if (r != ERROR_SUCCESS)
    {
        msiobj_release(&dbrec->hdr);
        return r;
    }

    count = MSI_RecordGetFieldCount(dbrec);
    for (i = 1; i <= count; i++)
    {
        if (!MSI_RecordGetString(mergerec, i))
            break;

        if (!merge_type_match(MSI_RecordGetString(dbrec, i),
                     MSI_RecordGetString(mergerec, i)))
        {
            r = ERROR_DATATYPE_MISMATCH;
            break;
        }
    }

done:
    msiobj_release(&dbrec->hdr);
    msiobj_release(&mergerec->hdr);

    return r;
}