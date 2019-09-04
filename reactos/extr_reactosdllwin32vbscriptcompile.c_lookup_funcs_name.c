#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ function_t ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
typedef  TYPE_2__ compile_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL lookup_funcs_name(compile_ctx_t *ctx, const WCHAR *name)
{
    function_t *iter;

    for(iter = ctx->funcs; iter; iter = iter->next) {
        if(!strcmpiW(iter->name, name))
            return TRUE;
    }

    return FALSE;
}