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
struct TYPE_3__ {int /*<<< orphan*/  option_explicit; int /*<<< orphan*/  parse_complete; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void parse_complete(parser_ctx_t *ctx, BOOL option_explicit)
{
    ctx->parse_complete = TRUE;
    ctx->option_explicit = option_explicit;
}