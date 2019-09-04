#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct string {size_t len; int /*<<< orphan*/ * data; } ;
struct parser {size_t idx; size_t len; int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int TK_SPACE ; 
 size_t get_token (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int wql_lex( void *p, struct parser *parser )
{
    struct string *str = p;
    int token = -1;
    do
    {
        parser->idx += parser->len;
        if (!parser->cmd[parser->idx]) return 0;
        parser->len = get_token( &parser->cmd[parser->idx], &token );
        if (!parser->len) break;

        str->data = &parser->cmd[parser->idx];
        str->len = parser->len;
    } while (token == TK_SPACE);
    return token;
}