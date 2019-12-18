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
struct TYPE_5__ {size_t szmcarea; size_t szallmcarea; int /*<<< orphan*/ * mcarea; int /*<<< orphan*/ * mcbot; int /*<<< orphan*/ * mctop; int /*<<< orphan*/  mcprot; scalar_t__* param; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_6__ {size_t size; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  MCode ;
typedef  TYPE_2__ MCLink ;

/* Variables and functions */
 size_t JIT_P_sizemcode ; 
 size_t LJ_PAGESIZE ; 
 int /*<<< orphan*/  MCPROT_GEN ; 
 scalar_t__ mcode_alloc (TYPE_1__*,size_t) ; 

__attribute__((used)) static void mcode_allocarea(jit_State *J)
{
  MCode *oldarea = J->mcarea;
  size_t sz = (size_t)J->param[JIT_P_sizemcode] << 10;
  sz = (sz + LJ_PAGESIZE-1) & ~(size_t)(LJ_PAGESIZE - 1);
  J->mcarea = (MCode *)mcode_alloc(J, sz);
  J->szmcarea = sz;
  J->mcprot = MCPROT_GEN;
  J->mctop = (MCode *)((char *)J->mcarea + J->szmcarea);
  J->mcbot = (MCode *)((char *)J->mcarea + sizeof(MCLink));
  ((MCLink *)J->mcarea)->next = oldarea;
  ((MCLink *)J->mcarea)->size = sz;
  J->szallmcarea += sz;
}