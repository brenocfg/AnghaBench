#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  column; struct TYPE_3__* next; } ;
typedef  TYPE_1__ column_info ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_BAD_QUERY_SYNTAX ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT check_columns( const column_info *col_info )
{
    const column_info *c1, *c2;

    /* check for two columns with the same name */
    for( c1 = col_info; c1; c1 = c1->next )
        for( c2 = c1->next; c2; c2 = c2->next )
            if (!strcmpW( c1->column, c2->column ))
                return ERROR_BAD_QUERY_SYNTAX;

    return ERROR_SUCCESS;
}