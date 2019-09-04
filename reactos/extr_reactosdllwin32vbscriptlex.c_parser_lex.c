#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* ptr; int last_token; char* last_nl; char* code; } ;
typedef  TYPE_1__ parser_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int parse_next_token (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  skip_spaces (TYPE_1__*) ; 
 int tNL ; 

int parser_lex(void *lval, parser_ctx_t *ctx)
{
    int ret;

    while(1) {
        ret = parse_next_token(lval, ctx);
        if(ret == '_') {
            skip_spaces(ctx);
            if(*ctx->ptr != '\n') {
                FIXME("'_' not followed by newline\n");
                return 0;
            }
            ctx->ptr++;
            continue;
        }
        if(ret != tNL || ctx->last_token != tNL)
            break;

        ctx->last_nl = ctx->ptr-ctx->code;
    }

    return (ctx->last_token = ret);
}