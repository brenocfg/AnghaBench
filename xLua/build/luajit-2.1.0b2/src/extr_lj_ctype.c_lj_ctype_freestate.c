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
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_6__ {int /*<<< orphan*/  sizeid; int /*<<< orphan*/  cbid; } ;
struct TYPE_7__ {TYPE_1__ cb; int /*<<< orphan*/  sizetab; int /*<<< orphan*/  tab; } ;
typedef  TYPE_2__ CTState ;

/* Variables and functions */
 int /*<<< orphan*/  CType ; 
 int /*<<< orphan*/  CTypeID1 ; 
 TYPE_2__* ctype_ctsG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_ccallback_mcode_free (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_mem_freet (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  lj_mem_freevec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lj_ctype_freestate(global_State *g)
{
  CTState *cts = ctype_ctsG(g);
  if (cts) {
    lj_ccallback_mcode_free(cts);
    lj_mem_freevec(g, cts->tab, cts->sizetab, CType);
    lj_mem_freevec(g, cts->cb.cbid, cts->cb.sizeid, CTypeID1);
    lj_mem_freet(g, cts);
  }
}