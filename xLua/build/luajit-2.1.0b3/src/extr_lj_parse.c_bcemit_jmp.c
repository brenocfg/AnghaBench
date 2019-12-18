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
typedef  scalar_t__ int32_t ;
struct TYPE_7__ {size_t jpc; size_t pc; size_t lasttarget; int /*<<< orphan*/  freereg; TYPE_1__* bcbase; } ;
struct TYPE_6__ {int /*<<< orphan*/  ins; } ;
typedef  TYPE_2__ FuncState ;
typedef  size_t BCPos ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 int /*<<< orphan*/  BC_JMP ; 
 scalar_t__ BC_UCLO ; 
 size_t NO_JMP ; 
 scalar_t__ bc_op (int /*<<< orphan*/ ) ; 
 size_t bcemit_AJ (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  jmp_append (TYPE_2__*,size_t*,size_t) ; 
 int /*<<< orphan*/  setbc_j (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static BCPos bcemit_jmp(FuncState *fs)
{
  BCPos jpc = fs->jpc;
  BCPos j = fs->pc - 1;
  BCIns *ip = &fs->bcbase[j].ins;
  fs->jpc = NO_JMP;
  if ((int32_t)j >= (int32_t)fs->lasttarget && bc_op(*ip) == BC_UCLO) {
    setbc_j(ip, NO_JMP);
    fs->lasttarget = j+1;
  } else {
    j = bcemit_AJ(fs, BC_JMP, fs->freereg, NO_JMP);
  }
  jmp_append(fs, &j, jpc);
  return j;
}