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
struct TYPE_3__ {int /*<<< orphan*/  end; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  strpbrkW (int /*<<< orphan*/ ,char const*) ; 
 int tNL ; 

__attribute__((used)) static int comment_line(parser_ctx_t *ctx)
{
    static const WCHAR newlineW[] = {'\n','\r',0};
    ctx->ptr = strpbrkW(ctx->ptr, newlineW);
    if(ctx->ptr)
        ctx->ptr++;
    else
        ctx->ptr = ctx->end;
    return tNL;
}