#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * mctop; int /*<<< orphan*/ * mcbot; int /*<<< orphan*/  mcarea; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  MCode ;

/* Variables and functions */
 int /*<<< orphan*/  MCPROT_GEN ; 
 int /*<<< orphan*/  mcode_allocarea (TYPE_1__*) ; 
 int /*<<< orphan*/  mcode_protect (TYPE_1__*,int /*<<< orphan*/ ) ; 

MCode *lj_mcode_reserve(jit_State *J, MCode **lim)
{
  if (!J->mcarea)
    mcode_allocarea(J);
  else
    mcode_protect(J, MCPROT_GEN);
  *lim = J->mcbot;
  return J->mctop;
}