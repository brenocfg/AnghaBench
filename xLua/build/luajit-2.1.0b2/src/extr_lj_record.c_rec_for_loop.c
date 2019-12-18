#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int start; } ;
struct TYPE_16__ {size_t maxslot; void** base; TYPE_3__ scev; TYPE_1__* L; } ;
typedef  TYPE_4__ jit_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_14__ {scalar_t__ irt; } ;
struct TYPE_17__ {int dir; int /*<<< orphan*/  pc; void* idx; void* step; void* stop; void* start; TYPE_2__ t; } ;
struct TYPE_13__ {int /*<<< orphan*/ * base; } ;
typedef  void* TRef ;
typedef  TYPE_5__ ScEvEntry ;
typedef  scalar_t__ IRType ;
typedef  size_t BCReg ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 scalar_t__ BC_FORI ; 
 scalar_t__ BC_JFORI ; 
 size_t FORL_EXT ; 
 size_t FORL_IDX ; 
 size_t FORL_STEP ; 
 size_t FORL_STOP ; 
 int IRSLOAD_INHERIT ; 
 int IRSLOAD_READONLY ; 
 int IRSLOAD_TYPECHECK ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IRT_INT ; 
 scalar_t__ IRT_NUM ; 
 int /*<<< orphan*/  IR_ADD ; 
 scalar_t__ LJ_DUALNUM ; 
 size_t bc_a (int /*<<< orphan*/  const) ; 
 scalar_t__ bc_op (int /*<<< orphan*/  const) ; 
 void* emitir (int /*<<< orphan*/ ,void*,void*) ; 
 void* find_kinit (TYPE_4__*,int /*<<< orphan*/  const*,size_t,scalar_t__) ; 
 void* fori_arg (TYPE_4__*,int /*<<< orphan*/  const*,size_t,scalar_t__,int) ; 
 void* fori_load (TYPE_4__*,size_t,scalar_t__,int) ; 
 scalar_t__ irref_isk (void*) ; 
 scalar_t__ lj_opt_narrow_forl (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  rec_for_check (TYPE_4__*,scalar_t__,int,void*,void*,int) ; 
 int rec_for_direction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 void* tref_ref (void*) ; 
 scalar_t__ tref_type (void*) ; 
 int tvisint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rec_for_loop(jit_State *J, const BCIns *fori, ScEvEntry *scev,
			 int init)
{
  BCReg ra = bc_a(*fori);
  cTValue *tv = &J->L->base[ra];
  TRef idx = J->base[ra+FORL_IDX];
  IRType t = idx ? tref_type(idx) :
	     (init || LJ_DUALNUM) ? lj_opt_narrow_forl(J, tv) : IRT_NUM;
  int mode = IRSLOAD_INHERIT +
    ((!LJ_DUALNUM || tvisint(tv) == (t == IRT_INT)) ? IRSLOAD_READONLY : 0);
  TRef stop = fori_arg(J, fori, ra+FORL_STOP, t, mode);
  TRef step = fori_arg(J, fori, ra+FORL_STEP, t, mode);
  int tc, dir = rec_for_direction(&tv[FORL_STEP]);
  lua_assert(bc_op(*fori) == BC_FORI || bc_op(*fori) == BC_JFORI);
  scev->t.irt = t;
  scev->dir = dir;
  scev->stop = tref_ref(stop);
  scev->step = tref_ref(step);
  rec_for_check(J, t, dir, stop, step, init);
  scev->start = tref_ref(find_kinit(J, fori, ra+FORL_IDX, IRT_INT));
  tc = (LJ_DUALNUM &&
	!(scev->start && irref_isk(scev->stop) && irref_isk(scev->step) &&
	  tvisint(&tv[FORL_IDX]) == (t == IRT_INT))) ?
	IRSLOAD_TYPECHECK : 0;
  if (tc) {
    J->base[ra+FORL_STOP] = stop;
    J->base[ra+FORL_STEP] = step;
  }
  if (!idx)
    idx = fori_load(J, ra+FORL_IDX, t,
		    IRSLOAD_INHERIT + tc + (J->scev.start << 16));
  if (!init)
    J->base[ra+FORL_IDX] = idx = emitir(IRT(IR_ADD, t), idx, step);
  J->base[ra+FORL_EXT] = idx;
  scev->idx = tref_ref(idx);
  setmref(scev->pc, fori);
  J->maxslot = ra+FORL_EXT+1;
}