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
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_6__ {TYPE_1__* ir; } ;
struct TYPE_5__ {int /*<<< orphan*/  t; int /*<<< orphan*/  prev; } ;
typedef  scalar_t__ TRef ;
typedef  int /*<<< orphan*/  SnapEntry ;
typedef  int /*<<< orphan*/  MSize ;
typedef  size_t IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ GCtrace ;
typedef  int /*<<< orphan*/  BloomFilter ;

/* Variables and functions */
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IR_PVAL ; 
 size_t REF_BIAS ; 
 int /*<<< orphan*/  bloomtest (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ emitir (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ irref_isk (size_t) ; 
 int /*<<< orphan*/  irt_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regsp_used (int /*<<< orphan*/ ) ; 
 scalar_t__ snap_dedup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ snap_replay_const (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static TRef snap_pref(jit_State *J, GCtrace *T, SnapEntry *map, MSize nmax,
		      BloomFilter seen, IRRef ref)
{
  IRIns *ir = &T->ir[ref];
  TRef tr;
  if (irref_isk(ref))
    tr = snap_replay_const(J, ir);
  else if (!regsp_used(ir->prev))
    tr = 0;
  else if (!bloomtest(seen, ref) || (tr = snap_dedup(J, map, nmax, ref)) == 0)
    tr = emitir(IRT(IR_PVAL, irt_type(ir->t)), ref - REF_BIAS, 0);
  return tr;
}