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
struct TYPE_4__ {int /*<<< orphan*/  sub_end_label; } ;
typedef  TYPE_1__ compile_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  exit_label (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_exitsub_statement(compile_ctx_t *ctx)
{
    if(!ctx->sub_end_label) {
        FIXME("Exit Sub outside Sub?\n");
        return E_FAIL;
    }

    return exit_label(ctx, ctx->sub_end_label);
}