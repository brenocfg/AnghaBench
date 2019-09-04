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
struct sql_str {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {size_t n; size_t len; int /*<<< orphan*/ * command; } ;
typedef  TYPE_1__ SQL_input ;

/* Variables and functions */
 int TK_SPACE ; 
 size_t sqliteGetToken (int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static int sql_lex( void *SQL_lval, SQL_input *sql )
{
    int token, skip;
    struct sql_str * str = SQL_lval;

    do
    {
        sql->n += sql->len;
        if( ! sql->command[sql->n] )
            return 0;  /* end of input */

        /* TRACE("string : %s\n", debugstr_w(&sql->command[sql->n])); */
        sql->len = sqliteGetToken( &sql->command[sql->n], &token, &skip );
        if( sql->len==0 )
            break;
        str->data = &sql->command[sql->n];
        str->len = sql->len;
        sql->n += skip;
    }
    while( token == TK_SPACE );

    /* TRACE("token : %d (%s)\n", token, debugstr_wn(&sql->command[sql->n], sql->len)); */

    return token;
}