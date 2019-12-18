#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int freetrace; int sizetrace; int /*<<< orphan*/ * trace; int /*<<< orphan*/  L; scalar_t__* param; } ;
typedef  TYPE_1__ jit_State ;
typedef  int TraceNo ;
typedef  int MSize ;

/* Variables and functions */
 int /*<<< orphan*/  GCRef ; 
 size_t JIT_P_maxtrace ; 
 int /*<<< orphan*/  lj_mem_growvec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcrefnull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * traceref (TYPE_1__*,int) ; 

__attribute__((used)) static TraceNo trace_findfree(jit_State *J)
{
  MSize osz, lim;
  if (J->freetrace == 0)
    J->freetrace = 1;
  for (; J->freetrace < J->sizetrace; J->freetrace++)
    if (traceref(J, J->freetrace) == NULL)
      return J->freetrace++;
  /* Need to grow trace array. */
  lim = (MSize)J->param[JIT_P_maxtrace] + 1;
  if (lim < 2) lim = 2; else if (lim > 65535) lim = 65535;
  osz = J->sizetrace;
  if (osz >= lim)
    return 0;  /* Too many traces. */
  lj_mem_growvec(J->L, J->trace, J->sizetrace, lim, GCRef);
  for (; osz < J->sizetrace; osz++)
    setgcrefnull(J->trace[osz]);
  return J->freetrace;
}