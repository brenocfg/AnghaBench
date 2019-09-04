#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  column; int /*<<< orphan*/  table; } ;
struct TYPE_10__ {int column; TYPE_5__* table; } ;
union ext_column {TYPE_3__ unparsed; TYPE_2__ parsed; } ;
typedef  int UINT ;
struct TYPE_14__ {TYPE_1__* ops; } ;
struct TYPE_13__ {int col_count; TYPE_6__* view; struct TYPE_13__* next; } ;
struct TYPE_12__ {TYPE_5__* tables; } ;
struct TYPE_9__ {int (* get_column_info ) (TYPE_6__*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__ MSIWHEREVIEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_5__ JOINTABLE ;

/* Variables and functions */
 int ERROR_BAD_QUERY_SYNTAX ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_6__*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_6__*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT parse_column(MSIWHEREVIEW *wv, union ext_column *column,
                         UINT *column_type)
{
    JOINTABLE *table = wv->tables;
    UINT i, r;

    do
    {
        LPCWSTR table_name;

        if (column->unparsed.table)
        {
            r = table->view->ops->get_column_info(table->view, 1, NULL, NULL,
                                                  NULL, &table_name);
            if (r != ERROR_SUCCESS)
                return r;
            if (strcmpW(table_name, column->unparsed.table) != 0)
                continue;
        }

        for(i = 1; i <= table->col_count; i++)
        {
            LPCWSTR col_name;

            r = table->view->ops->get_column_info(table->view, i, &col_name, column_type,
                                                  NULL, NULL);
            if(r != ERROR_SUCCESS )
                return r;

            if(strcmpW(col_name, column->unparsed.column))
                continue;
            column->parsed.column = i;
            column->parsed.table = table;
            return ERROR_SUCCESS;
        }
    }
    while ((table = table->next));

    WARN("Couldn't find column %s.%s\n", debugstr_w( column->unparsed.table ), debugstr_w( column->unparsed.column ) );
    return ERROR_BAD_QUERY_SYNTAX;
}