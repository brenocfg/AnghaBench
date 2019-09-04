#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;
struct TYPE_6__ {int /*<<< orphan*/ * kid; int /*<<< orphan*/ * next; int /*<<< orphan*/  op; } ;
typedef  int /*<<< orphan*/  REOp ;
typedef  TYPE_1__ RENode ;
typedef  TYPE_2__ CompilerState ;

/* Variables and functions */
 TYPE_1__* heap_pool_alloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static RENode *
NewRENode(CompilerState *state, REOp op)
{
    RENode *ren;

    ren = heap_pool_alloc(state->pool, sizeof(*ren));
    if (!ren) {
        /* js_ReportOutOfScriptQuota(cx); */
        return NULL;
    }
    ren->op = op;
    ren->next = NULL;
    ren->kid = NULL;
    return ren;
}