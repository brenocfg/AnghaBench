#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ a; TYPE_1__** curctx; int /*<<< orphan*/  c; } ;
typedef  TYPE_2__ opj_mqc_t ;
struct TYPE_5__ {scalar_t__ qeval; struct TYPE_5__* nlps; } ;

/* Variables and functions */
 int /*<<< orphan*/  opj_mqc_renorme (TYPE_2__*) ; 

__attribute__((used)) static void opj_mqc_codelps(opj_mqc_t *mqc)
{
    mqc->a -= (*mqc->curctx)->qeval;
    if (mqc->a < (*mqc->curctx)->qeval) {
        mqc->c += (*mqc->curctx)->qeval;
    } else {
        mqc->a = (*mqc->curctx)->qeval;
    }
    *mqc->curctx = (*mqc->curctx)->nlps;
    opj_mqc_renorme(mqc);
}