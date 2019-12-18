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
struct TYPE_5__ {scalar_t__ szallmcarea; int /*<<< orphan*/ * mcarea; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  MCode ;
typedef  TYPE_2__ MCLink ;

/* Variables and functions */
 int /*<<< orphan*/  mcode_free (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lj_mcode_free(jit_State *J)
{
  MCode *mc = J->mcarea;
  J->mcarea = NULL;
  J->szallmcarea = 0;
  while (mc) {
    MCode *next = ((MCLink *)mc)->next;
    mcode_free(J, mc, ((MCLink *)mc)->size);
    mc = next;
  }
}