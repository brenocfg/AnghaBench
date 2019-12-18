#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int dispatchmode; int hookmask; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_10__ {int /*<<< orphan*/ * dispatch; } ;
struct TYPE_9__ {int flags; scalar_t__ state; } ;
typedef  int /*<<< orphan*/  ASMFunction ;

/* Variables and functions */
 size_t BC_FORL ; 
 size_t BC_FUNCF ; 
 size_t BC_FUNCV ; 
 size_t BC_IFORL ; 
 size_t BC_IFUNCF ; 
 size_t BC_IFUNCV ; 
 size_t BC_IITERL ; 
 size_t BC_ILOOP ; 
 size_t BC_ITERL ; 
 size_t BC_LOOP ; 
 size_t BC_RET ; 
 size_t BC_RET0 ; 
 size_t BC_RET1 ; 
 size_t BC_RETM ; 
 int DISPMODE_CALL ; 
 int DISPMODE_INS ; 
 int DISPMODE_JIT ; 
 int DISPMODE_PROF ; 
 int DISPMODE_REC ; 
 int DISPMODE_RET ; 
 TYPE_6__* G2GG (TYPE_1__*) ; 
 TYPE_4__* G2J (TYPE_1__*) ; 
 size_t GG_LEN_DDISP ; 
 int GG_LEN_SDISP ; 
 int HOOK_PROFILE ; 
 int JIT_F_ON ; 
 scalar_t__ LJ_TRACE_IDLE ; 
 int LUA_MASKCALL ; 
 int LUA_MASKCOUNT ; 
 int LUA_MASKLINE ; 
 int LUA_MASKRET ; 
 int /*<<< orphan*/ * lj_bc_ofs ; 
 int /*<<< orphan*/  lj_dispatch_init_hotcount (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_vm_callhook ; 
 int /*<<< orphan*/  lj_vm_inshook ; 
 int /*<<< orphan*/  lj_vm_profhook ; 
 int /*<<< orphan*/  lj_vm_record ; 
 int /*<<< orphan*/  lj_vm_rethook ; 
 int /*<<< orphan*/  makeasmfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void lj_dispatch_update(global_State *g)
{
  uint8_t oldmode = g->dispatchmode;
  uint8_t mode = 0;
#if LJ_HASJIT
  mode |= (G2J(g)->flags & JIT_F_ON) ? DISPMODE_JIT : 0;
  mode |= G2J(g)->state != LJ_TRACE_IDLE ?
	    (DISPMODE_REC|DISPMODE_INS|DISPMODE_CALL) : 0;
#endif
#if LJ_HASPROFILE
  mode |= (g->hookmask & HOOK_PROFILE) ? (DISPMODE_PROF|DISPMODE_INS) : 0;
#endif
  mode |= (g->hookmask & (LUA_MASKLINE|LUA_MASKCOUNT)) ? DISPMODE_INS : 0;
  mode |= (g->hookmask & LUA_MASKCALL) ? DISPMODE_CALL : 0;
  mode |= (g->hookmask & LUA_MASKRET) ? DISPMODE_RET : 0;
  if (oldmode != mode) {  /* Mode changed? */
    ASMFunction *disp = G2GG(g)->dispatch;
    ASMFunction f_forl, f_iterl, f_loop, f_funcf, f_funcv;
    g->dispatchmode = mode;

    /* Hotcount if JIT is on, but not while recording. */
    if ((mode & (DISPMODE_JIT|DISPMODE_REC)) == DISPMODE_JIT) {
      f_forl = makeasmfunc(lj_bc_ofs[BC_FORL]);
      f_iterl = makeasmfunc(lj_bc_ofs[BC_ITERL]);
      f_loop = makeasmfunc(lj_bc_ofs[BC_LOOP]);
      f_funcf = makeasmfunc(lj_bc_ofs[BC_FUNCF]);
      f_funcv = makeasmfunc(lj_bc_ofs[BC_FUNCV]);
    } else {  /* Otherwise use the non-hotcounting instructions. */
      f_forl = disp[GG_LEN_DDISP+BC_IFORL];
      f_iterl = disp[GG_LEN_DDISP+BC_IITERL];
      f_loop = disp[GG_LEN_DDISP+BC_ILOOP];
      f_funcf = makeasmfunc(lj_bc_ofs[BC_IFUNCF]);
      f_funcv = makeasmfunc(lj_bc_ofs[BC_IFUNCV]);
    }
    /* Init static counting instruction dispatch first (may be copied below). */
    disp[GG_LEN_DDISP+BC_FORL] = f_forl;
    disp[GG_LEN_DDISP+BC_ITERL] = f_iterl;
    disp[GG_LEN_DDISP+BC_LOOP] = f_loop;

    /* Set dynamic instruction dispatch. */
    if ((oldmode ^ mode) & (DISPMODE_PROF|DISPMODE_REC|DISPMODE_INS)) {
      /* Need to update the whole table. */
      if (!(mode & DISPMODE_INS)) {  /* No ins dispatch? */
	/* Copy static dispatch table to dynamic dispatch table. */
	memcpy(&disp[0], &disp[GG_LEN_DDISP], GG_LEN_SDISP*sizeof(ASMFunction));
	/* Overwrite with dynamic return dispatch. */
	if ((mode & DISPMODE_RET)) {
	  disp[BC_RETM] = lj_vm_rethook;
	  disp[BC_RET] = lj_vm_rethook;
	  disp[BC_RET0] = lj_vm_rethook;
	  disp[BC_RET1] = lj_vm_rethook;
	}
      } else {
	/* The recording dispatch also checks for hooks. */
	ASMFunction f = (mode & DISPMODE_PROF) ? lj_vm_profhook :
			(mode & DISPMODE_REC) ? lj_vm_record : lj_vm_inshook;
	uint32_t i;
	for (i = 0; i < GG_LEN_SDISP; i++)
	  disp[i] = f;
      }
    } else if (!(mode & DISPMODE_INS)) {
      /* Otherwise set dynamic counting ins. */
      disp[BC_FORL] = f_forl;
      disp[BC_ITERL] = f_iterl;
      disp[BC_LOOP] = f_loop;
      /* Set dynamic return dispatch. */
      if ((mode & DISPMODE_RET)) {
	disp[BC_RETM] = lj_vm_rethook;
	disp[BC_RET] = lj_vm_rethook;
	disp[BC_RET0] = lj_vm_rethook;
	disp[BC_RET1] = lj_vm_rethook;
      } else {
	disp[BC_RETM] = disp[GG_LEN_DDISP+BC_RETM];
	disp[BC_RET] = disp[GG_LEN_DDISP+BC_RET];
	disp[BC_RET0] = disp[GG_LEN_DDISP+BC_RET0];
	disp[BC_RET1] = disp[GG_LEN_DDISP+BC_RET1];
      }
    }

    /* Set dynamic call dispatch. */
    if ((oldmode ^ mode) & DISPMODE_CALL) {  /* Update the whole table? */
      uint32_t i;
      if ((mode & DISPMODE_CALL) == 0) {  /* No call hooks? */
	for (i = GG_LEN_SDISP; i < GG_LEN_DDISP; i++)
	  disp[i] = makeasmfunc(lj_bc_ofs[i]);
      } else {
	for (i = GG_LEN_SDISP; i < GG_LEN_DDISP; i++)
	  disp[i] = lj_vm_callhook;
      }
    }
    if (!(mode & DISPMODE_CALL)) {  /* Overwrite dynamic counting ins. */
      disp[BC_FUNCF] = f_funcf;
      disp[BC_FUNCV] = f_funcv;
    }

#if LJ_HASJIT
    /* Reset hotcounts for JIT off to on transition. */
    if ((mode & DISPMODE_JIT) && !(oldmode & DISPMODE_JIT))
      lj_dispatch_init_hotcount(g);
#endif
  }
}