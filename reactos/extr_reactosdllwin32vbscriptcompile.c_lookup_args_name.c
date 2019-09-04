#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* func; } ;
typedef  TYPE_3__ compile_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {unsigned int arg_cnt; TYPE_1__* args; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL lookup_args_name(compile_ctx_t *ctx, const WCHAR *name)
{
    unsigned i;

    for(i = 0; i < ctx->func->arg_cnt; i++) {
        if(!strcmpiW(ctx->func->args[i].name, name))
            return TRUE;
    }

    return FALSE;
}