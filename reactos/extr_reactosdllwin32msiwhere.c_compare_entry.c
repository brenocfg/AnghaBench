#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  column; TYPE_2__* table; } ;
union ext_column {TYPE_3__ parsed; } ;
typedef  size_t UINT ;
struct TYPE_15__ {TYPE_1__* ops; } ;
struct TYPE_14__ {size_t col_count; size_t error; union ext_column* columns; } ;
struct TYPE_13__ {scalar_t__* values; TYPE_4__* wv; } ;
struct TYPE_12__ {size_t table_count; TYPE_6__* order_info; } ;
struct TYPE_10__ {size_t table_index; TYPE_7__* view; } ;
struct TYPE_9__ {size_t (* fetch_int ) (TYPE_7__*,scalar_t__,int /*<<< orphan*/ ,size_t*) ;} ;
typedef  TYPE_4__ MSIWHEREVIEW ;
typedef  TYPE_5__ MSIROWENTRY ;
typedef  TYPE_6__ MSIORDERINFO ;

/* Variables and functions */
 size_t ERROR_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t stub1 (TYPE_7__*,scalar_t__,int /*<<< orphan*/ ,size_t*) ; 
 size_t stub2 (TYPE_7__*,scalar_t__,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int compare_entry( const void *left, const void *right )
{
    const MSIROWENTRY *le = *(const MSIROWENTRY**)left;
    const MSIROWENTRY *re = *(const MSIROWENTRY**)right;
    const MSIWHEREVIEW *wv = le->wv;
    MSIORDERINFO *order = wv->order_info;
    UINT i, j, r, l_val, r_val;

    assert(le->wv == re->wv);

    if (order)
    {
        for (i = 0; i < order->col_count; i++)
        {
            const union ext_column *column = &order->columns[i];

            r = column->parsed.table->view->ops->fetch_int(column->parsed.table->view,
                          le->values[column->parsed.table->table_index],
                          column->parsed.column, &l_val);
            if (r != ERROR_SUCCESS)
            {
                order->error = r;
                return 0;
            }

            r = column->parsed.table->view->ops->fetch_int(column->parsed.table->view,
                          re->values[column->parsed.table->table_index],
                          column->parsed.column, &r_val);
            if (r != ERROR_SUCCESS)
            {
                order->error = r;
                return 0;
            }

            if (l_val != r_val)
                return l_val < r_val ? -1 : 1;
        }
    }

    for (j = 0; j < wv->table_count; j++)
    {
        if (le->values[j] != re->values[j])
            return le->values[j] < re->values[j] ? -1 : 1;
    }
    return 0;
}