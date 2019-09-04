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
struct TYPE_5__ {scalar_t__* ptr; scalar_t__* end; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  scalar_t__ WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  JS_E_UNTERMINATED_STRING ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int lex_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__* parser_alloc (TYPE_1__*,int) ; 
 int tStringLiteral ; 
 int /*<<< orphan*/  unescape (scalar_t__*) ; 

__attribute__((used)) static int parse_string_literal(parser_ctx_t *ctx, const WCHAR **ret, WCHAR endch)
{
    const WCHAR *ptr = ++ctx->ptr;
    WCHAR *wstr;
    int len;

    while(ctx->ptr < ctx->end && *ctx->ptr != endch) {
        if(*ctx->ptr++ == '\\')
            ctx->ptr++;
    }

    if(ctx->ptr == ctx->end)
        return lex_error(ctx, JS_E_UNTERMINATED_STRING);

    len = ctx->ptr-ptr;

    *ret = wstr = parser_alloc(ctx, (len+1)*sizeof(WCHAR));
    memcpy(wstr, ptr, len*sizeof(WCHAR));
    wstr[len] = 0;

    ctx->ptr++;

    if(!unescape(wstr)) {
        WARN("unescape failed\n");
        return lex_error(ctx, E_FAIL);
    }

    return tStringLiteral;
}