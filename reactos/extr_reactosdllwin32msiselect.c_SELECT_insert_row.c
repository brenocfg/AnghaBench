#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {TYPE_1__* ops; } ;
struct TYPE_15__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_14__ {scalar_t__ num_cols; TYPE_4__* table; int /*<<< orphan*/ * cols; } ;
struct TYPE_13__ {scalar_t__ (* get_dimensions ) (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__*) ;scalar_t__ (* insert_row ) (TYPE_4__*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ MSISELECTVIEW ;
typedef  TYPE_3__ MSIRECORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 TYPE_3__* MSI_CreateRecord (scalar_t__) ; 
 scalar_t__ MSI_RecordCopyField (TYPE_3__*,scalar_t__,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ stub2 (TYPE_4__*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT SELECT_insert_row( struct tagMSIVIEW *view, MSIRECORD *record, UINT row, BOOL temporary )
{
    MSISELECTVIEW *sv = (MSISELECTVIEW*)view;
    UINT i, table_cols, r;
    MSIRECORD *outrec;

    TRACE("%p %p\n", sv, record );

    if ( !sv->table )
        return ERROR_FUNCTION_FAILED;

    /* rearrange the record to suit the table */
    r = sv->table->ops->get_dimensions( sv->table, NULL, &table_cols );
    if (r != ERROR_SUCCESS)
        return r;

    outrec = MSI_CreateRecord( table_cols + 1 );

    for (i=0; i<sv->num_cols; i++)
    {
        r = MSI_RecordCopyField( record, i+1, outrec, sv->cols[i] );
        if (r != ERROR_SUCCESS)
            goto fail;
    }

    r = sv->table->ops->insert_row( sv->table, outrec, row, temporary );

fail:
    msiobj_release( &outrec->hdr );

    return r;
}