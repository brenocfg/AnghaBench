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
struct TYPE_5__ {int /*<<< orphan*/  ls; TYPE_1__* bcbase; } ;
struct TYPE_4__ {int /*<<< orphan*/  ins; } ;
typedef  TYPE_2__ FuncState ;
typedef  size_t BCPos ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 size_t BCBIAS_J ; 
 size_t BCMAX_D ; 
 int /*<<< orphan*/  LJ_ERR_XJUMP ; 
 size_t NO_JMP ; 
 int /*<<< orphan*/  err_syntax (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setbc_d (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void jmp_patchins(FuncState *fs, BCPos pc, BCPos dest)
{
  BCIns *jmp = &fs->bcbase[pc].ins;
  BCPos offset = dest-(pc+1)+BCBIAS_J;
  lua_assert(dest != NO_JMP);
  if (offset > BCMAX_D)
    err_syntax(fs->ls, LJ_ERR_XJUMP);
  setbc_d(jmp, offset);
}