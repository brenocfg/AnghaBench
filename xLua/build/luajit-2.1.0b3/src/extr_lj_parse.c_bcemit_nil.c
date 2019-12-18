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
struct TYPE_6__ {int pc; int lasttarget; TYPE_1__* bcbase; } ;
struct TYPE_5__ {int /*<<< orphan*/  ins; } ;
typedef  TYPE_2__ FuncState ;
typedef  int BCReg ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 int /*<<< orphan*/  BCINS_AD (int const,int,int) ; 
#define  BC_KNIL 129 
#define  BC_KPRI 128 
 int LJ_TNIL ; 
 int VKNIL ; 
 int bc_a (int /*<<< orphan*/ ) ; 
 int bc_d (int /*<<< orphan*/ ) ; 
 int bc_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcemit_INS (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbc_d (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bcemit_nil(FuncState *fs, BCReg from, BCReg n)
{
  if (fs->pc > fs->lasttarget) {  /* No jumps to current position? */
    BCIns *ip = &fs->bcbase[fs->pc-1].ins;
    BCReg pto, pfrom = bc_a(*ip);
    switch (bc_op(*ip)) {  /* Try to merge with the previous instruction. */
    case BC_KPRI:
      if (bc_d(*ip) != ~LJ_TNIL) break;
      if (from == pfrom) {
	if (n == 1) return;
      } else if (from == pfrom+1) {
	from = pfrom;
	n++;
      } else {
	break;
      }
      *ip = BCINS_AD(BC_KNIL, from, from+n-1);  /* Replace KPRI. */
      return;
    case BC_KNIL:
      pto = bc_d(*ip);
      if (pfrom <= from && from <= pto+1) {  /* Can we connect both ranges? */
	if (from+n-1 > pto)
	  setbc_d(ip, from+n-1);  /* Patch previous instruction range. */
	return;
      }
      break;
    default:
      break;
    }
  }
  /* Emit new instruction or replace old instruction. */
  bcemit_INS(fs, n == 1 ? BCINS_AD(BC_KPRI, from, VKNIL) :
			  BCINS_AD(BC_KNIL, from, from+n-1));
}