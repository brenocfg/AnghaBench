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
struct TYPE_15__ {struct TYPE_15__* next; TYPE_2__* val; } ;
typedef  TYPE_3__ column_info ;
typedef  int UINT ;
struct TYPE_16__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_13__ {int /*<<< orphan*/  ival; int /*<<< orphan*/  sval; } ;
struct TYPE_14__ {int type; TYPE_1__ u; } ;
typedef  TYPE_4__ MSIRECORD ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  EXPR_IVAL 130 
#define  EXPR_SVAL 129 
#define  EXPR_WILDCARD 128 
 TYPE_4__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_RecordCopyField (TYPE_4__*,int,TYPE_4__*,int) ; 
 int /*<<< orphan*/  MSI_RecordSetInteger (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

MSIRECORD *msi_query_merge_record( UINT fields, const column_info *vl, MSIRECORD *rec )
{
    MSIRECORD *merged;
    DWORD wildcard_count = 1, i;

    merged = MSI_CreateRecord( fields );
    for( i=1; i <= fields; i++ )
    {
        if( !vl )
        {
            TRACE("Not enough elements in the list to insert\n");
            goto err;
        }
        switch( vl->val->type )
        {
        case EXPR_SVAL:
            TRACE("field %d -> %s\n", i, debugstr_w(vl->val->u.sval));
            MSI_RecordSetStringW( merged, i, vl->val->u.sval );
            break;
        case EXPR_IVAL:
            MSI_RecordSetInteger( merged, i, vl->val->u.ival );
            break;
        case EXPR_WILDCARD:
            if( !rec )
                goto err;
            MSI_RecordCopyField( rec, wildcard_count, merged, i );
            wildcard_count++;
            break;
        default:
            ERR("Unknown expression type %d\n", vl->val->type);
        }
        vl = vl->next;
    }

    return merged;
err:
    msiobj_release( &merged->hdr );
    return NULL;
}