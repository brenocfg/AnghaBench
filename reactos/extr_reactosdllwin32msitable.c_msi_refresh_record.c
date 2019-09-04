#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSI_CloseRecord (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSI_RecordCopyField (TYPE_1__*,scalar_t__,TYPE_1__*,scalar_t__) ; 
 scalar_t__ MSI_RecordGetFieldCount (TYPE_1__*) ; 
 scalar_t__ TABLE_get_row (struct tagMSIVIEW*,scalar_t__,TYPE_1__**) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT msi_refresh_record( struct tagMSIVIEW *view, MSIRECORD *rec, UINT row )
{
    MSIRECORD *curr;
    UINT r, i, count;

    r = TABLE_get_row(view, row - 1, &curr);
    if (r != ERROR_SUCCESS)
        return r;

    /* Close the original record */
    MSI_CloseRecord(&rec->hdr);

    count = MSI_RecordGetFieldCount(rec);
    for (i = 0; i < count; i++)
        MSI_RecordCopyField(curr, i + 1, rec, i + 1);

    msiobj_release(&curr->hdr);
    return ERROR_SUCCESS;
}