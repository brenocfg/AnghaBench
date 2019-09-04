#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_20__ {TYPE_1__* ops; } ;
struct TYPE_19__ {TYPE_2__* ops; } ;
struct TYPE_18__ {TYPE_5__* table; TYPE_6__* sv; } ;
struct TYPE_17__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_16__ {scalar_t__ (* get_dimensions ) (TYPE_5__*,int /*<<< orphan*/ *,scalar_t__*) ;scalar_t__ (* get_column_info ) (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_15__ {scalar_t__ (* get_column_info ) (TYPE_6__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ MSIRECORD ;
typedef  TYPE_4__ MSIINSERTVIEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 TYPE_3__* MSI_CreateRecord (scalar_t__) ; 
 int /*<<< orphan*/  MSI_RecordCopyField (TYPE_3__*,scalar_t__,TYPE_3__*,scalar_t__) ; 
 scalar_t__ MSI_RecordGetFieldCount (TYPE_3__*) ; 
 scalar_t__ msi_columns_in_order (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_5__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ stub2 (TYPE_6__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT msi_arrange_record(MSIINSERTVIEW *iv, MSIRECORD **values)
{
    MSIRECORD *padded;
    UINT col_count, val_count;
    UINT r, i, colidx;
    LPCWSTR a, b;

    r = iv->table->ops->get_dimensions(iv->table, NULL, &col_count);
    if (r != ERROR_SUCCESS)
        return r;

    val_count = MSI_RecordGetFieldCount(*values);

    /* check to see if the columns are arranged already
     * to avoid unnecessary copying
     */
    if (col_count == val_count && msi_columns_in_order(iv, col_count))
        return ERROR_SUCCESS;

    padded = MSI_CreateRecord(col_count);
    if (!padded)
        return ERROR_OUTOFMEMORY;

    for (colidx = 1; colidx <= val_count; colidx++)
    {
        r = iv->sv->ops->get_column_info(iv->sv, colidx, &a, NULL, NULL, NULL);
        if (r != ERROR_SUCCESS)
            goto err;

        for (i = 1; i <= col_count; i++)
        {
            r = iv->table->ops->get_column_info(iv->table, i, &b, NULL,
                                                NULL, NULL);
            if (r != ERROR_SUCCESS)
                goto err;

            if (!strcmpW( a, b ))
            {
                MSI_RecordCopyField(*values, colidx, padded, i);
                break;
            }
        }
    }
    msiobj_release(&(*values)->hdr);
    *values = padded;
    return ERROR_SUCCESS;

err:
    msiobj_release(&padded->hdr);
    return r;
}