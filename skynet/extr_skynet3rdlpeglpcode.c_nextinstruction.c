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
struct TYPE_5__ {int codesize; } ;
struct TYPE_4__ {int ncode; TYPE_2__* p; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ CompileState ;

/* Variables and functions */
 int /*<<< orphan*/  realloccode (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static int nextinstruction (CompileState *compst) {
  int size = compst->p->codesize;
  if (compst->ncode >= size)
    realloccode(compst->L, compst->p, size * 2);
  return compst->ncode++;
}