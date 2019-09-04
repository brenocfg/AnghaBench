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
typedef  int UINT ;
struct TYPE_16__ {TYPE_1__* ops; } ;
struct TYPE_15__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_14__ {int num_cols; int* cols; TYPE_4__* table; } ;
struct TYPE_13__ {int (* get_dimensions ) (TYPE_4__*,int /*<<< orphan*/ *,int*) ;int (* set_row ) (TYPE_4__*,int,TYPE_3__*,int) ;} ;
typedef  TYPE_2__ MSISELECTVIEW ;
typedef  TYPE_3__ MSIRECORD ;

/* Variables and functions */
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 TYPE_3__* MSI_CreateRecord (int) ; 
 int MSI_RecordCopyField (TYPE_3__*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ *,int*) ; 
 int stub2 (TYPE_4__*,int,TYPE_3__*,int) ; 

__attribute__((used)) static UINT SELECT_set_row( struct tagMSIVIEW *view, UINT row, MSIRECORD *rec, UINT mask )
{
    MSISELECTVIEW *sv = (MSISELECTVIEW*)view;
    UINT i, expanded_mask = 0, r = ERROR_SUCCESS, col_count = 0;
    MSIRECORD *expanded;

    TRACE("%p %d %p %08x\n", sv, row, rec, mask );

    if ( !sv->table )
         return ERROR_FUNCTION_FAILED;

    /* test if any of the mask bits are invalid */
    if ( mask >= (1<<sv->num_cols) )
        return ERROR_INVALID_PARAMETER;

    /* find the number of columns in the table below */
    r = sv->table->ops->get_dimensions( sv->table, NULL, &col_count );
    if( r )
        return r;

    /* expand the record to the right size for the underlying table */
    expanded = MSI_CreateRecord( col_count );
    if ( !expanded )
        return ERROR_FUNCTION_FAILED;

    /* move the right fields across */
    for ( i=0; i<sv->num_cols; i++ )
    {
        r = MSI_RecordCopyField( rec, i+1, expanded, sv->cols[ i ] );
        if (r != ERROR_SUCCESS)
            break;
        expanded_mask |= (1<<(sv->cols[i]-1));
    }

    /* set the row in the underlying table */
    if (r == ERROR_SUCCESS)
        r = sv->table->ops->set_row( sv->table, row, expanded, expanded_mask );

    msiobj_release( &expanded->hdr );
    return r;
}