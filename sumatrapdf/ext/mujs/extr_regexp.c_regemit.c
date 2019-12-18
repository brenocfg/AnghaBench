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
struct TYPE_6__ {int opcode; int /*<<< orphan*/ * y; int /*<<< orphan*/  x; int /*<<< orphan*/ * cc; scalar_t__ c; scalar_t__ n; } ;
struct TYPE_5__ {int /*<<< orphan*/  end; } ;
typedef  TYPE_1__ Reprog ;
typedef  TYPE_2__ Reinst ;

/* Variables and functions */

__attribute__((used)) static Reinst *emit(Reprog *prog, int opcode)
{
	Reinst *inst = prog->end++;
	inst->opcode = opcode;
	inst->n = 0;
	inst->c = 0;
	inst->cc = NULL;
	inst->x = inst->y = NULL;
	return inst;
}