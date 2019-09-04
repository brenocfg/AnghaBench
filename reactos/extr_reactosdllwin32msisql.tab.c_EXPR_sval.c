#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sql_str {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sval; } ;
struct expr {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EXPR_SVAL ; 
 scalar_t__ SQL_getstring (void*,struct sql_str const*,int /*<<< orphan*/ *) ; 
 struct expr* parser_alloc (void*,int) ; 

__attribute__((used)) static struct expr * EXPR_sval( void *info, const struct sql_str *str )
{
    struct expr *e = parser_alloc( info, sizeof *e );
    if( e )
    {
        e->type = EXPR_SVAL;
        if( SQL_getstring( info, str, (LPWSTR *)&e->u.sval ) != ERROR_SUCCESS )
            return NULL; /* e will be freed by query destructor */
    }
    return e;
}