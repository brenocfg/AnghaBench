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
struct TYPE_3__ {char const* ptr; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  char const WCHAR ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int hex_to_int (char const) ; 
 scalar_t__ is_identifier_char (char) ; 
 int tLong ; 
 int tShort ; 

__attribute__((used)) static int parse_hex_literal(parser_ctx_t *ctx, LONG *ret)
{
    const WCHAR *begin = ctx->ptr;
    LONG l = 0, d;

    while((d = hex_to_int(*++ctx->ptr)) != -1)
        l = l*16 + d;

    if(begin + 9 /* max digits+1 */ < ctx->ptr || (*ctx->ptr != '&' && is_identifier_char(*ctx->ptr))) {
        FIXME("invalid literal\n");
        return 0;
    }

    if(*ctx->ptr == '&')
        ctx->ptr++;

    *ret = l;
    return (short)l == l ? tShort : tLong;
}