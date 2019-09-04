#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct list {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {TYPE_1__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  r; TYPE_3__** view; struct list* mem; scalar_t__ len; scalar_t__ n; int /*<<< orphan*/  command; int /*<<< orphan*/ * db; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* delete ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ SQL_input ;
typedef  TYPE_3__ MSIVIEW ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_BAD_QUERY_SYNTAX ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int sql_parse (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

UINT MSI_ParseSQL( MSIDATABASE *db, LPCWSTR command, MSIVIEW **phview,
                   struct list *mem )
{
    SQL_input sql;
    int r;

    *phview = NULL;

    sql.db = db;
    sql.command = command;
    sql.n = 0;
    sql.len = 0;
    sql.r = ERROR_BAD_QUERY_SYNTAX;
    sql.view = phview;
    sql.mem = mem;

    r = sql_parse(&sql);

    TRACE("Parse returned %d\n", r);
    if( r )
    {
        if (*sql.view)
        {
            (*sql.view)->ops->delete(*sql.view);
            *sql.view = NULL;
        }
        return sql.r;
    }

    return ERROR_SUCCESS;
}