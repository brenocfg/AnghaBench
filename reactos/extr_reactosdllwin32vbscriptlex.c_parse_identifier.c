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
struct TYPE_4__ {scalar_t__ const* ptr; scalar_t__ const* end; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  scalar_t__ WCHAR ;

/* Variables and functions */
 scalar_t__ is_identifier_char (scalar_t__ const) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__* parser_alloc (TYPE_1__*,int) ; 
 int tIdentifier ; 

__attribute__((used)) static int parse_identifier(parser_ctx_t *ctx, const WCHAR **ret)
{
    const WCHAR *ptr = ctx->ptr++;
    WCHAR *str;
    int len;

    while(ctx->ptr < ctx->end && is_identifier_char(*ctx->ptr))
        ctx->ptr++;
    len = ctx->ptr-ptr;

    str = parser_alloc(ctx, (len+1)*sizeof(WCHAR));
    if(!str)
        return 0;

    memcpy(str, ptr, (len+1)*sizeof(WCHAR));
    str[len] = 0;
    *ret = str;
    return tIdentifier;
}