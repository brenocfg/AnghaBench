#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* ptr; char* end; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 char* parser_alloc (TYPE_1__*,int) ; 
 int tString ; 

__attribute__((used)) static int parse_string_literal(parser_ctx_t *ctx, const WCHAR **ret)
{
    const WCHAR *ptr = ++ctx->ptr;
    WCHAR *rptr;
    int len = 0;

    while(ctx->ptr < ctx->end) {
        if(*ctx->ptr == '\n') {
            FIXME("newline inside string literal\n");
            return 0;
        }

       if(*ctx->ptr == '"') {
            if(ctx->ptr[1] != '"')
                break;
            len--;
            ctx->ptr++;
        }
        ctx->ptr++;
    }

    if(ctx->ptr == ctx->end) {
        FIXME("unterminated string literal\n");
        return 0;
    }

    len += ctx->ptr-ptr;

    *ret = rptr = parser_alloc(ctx, (len+1)*sizeof(WCHAR));
    if(!rptr)
        return 0;

    while(ptr < ctx->ptr) {
        if(*ptr == '"')
            ptr++;
        *rptr++ = *ptr++;
    }

    *rptr = 0;
    ctx->ptr++;
    return tString;
}