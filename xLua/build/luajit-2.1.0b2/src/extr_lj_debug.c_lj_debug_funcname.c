#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  stack; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_10__ {scalar_t__ sizebc; } ;
typedef  scalar_t__ MMS ;
typedef  TYPE_2__ GCproto ;
typedef  int /*<<< orphan*/  GCfunc ;
typedef  int BCReg ;
typedef  scalar_t__ BCPos ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 scalar_t__ BC_ITERC ; 
 int /*<<< orphan*/  G (TYPE_1__*) ; 
 int LJ_FR2 ; 
 scalar_t__ MM__MAX ; 
 scalar_t__ MM_call ; 
 scalar_t__ NO_BCPOS ; 
 int bc_a (int /*<<< orphan*/  const) ; 
 scalar_t__ bc_op (int /*<<< orphan*/  const) ; 
 scalar_t__ bcmode_mm (scalar_t__) ; 
 size_t check_exp (int,scalar_t__) ; 
 scalar_t__ debug_framepc (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_func (int /*<<< orphan*/ *) ; 
 scalar_t__ frame_isvarg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_prev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_prevd (int /*<<< orphan*/ *) ; 
 TYPE_2__* funcproto (int /*<<< orphan*/ *) ; 
 char const* lj_debug_slotname (TYPE_2__*,int /*<<< orphan*/  const*,int,char const**) ; 
 int /*<<< orphan*/  mmname_str (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * proto_bc (TYPE_2__*) ; 
 char* strdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

const char *lj_debug_funcname(lua_State *L, cTValue *frame, const char **name)
{
  cTValue *pframe;
  GCfunc *fn;
  BCPos pc;
  if (frame <= tvref(L->stack)+LJ_FR2)
    return NULL;
  if (frame_isvarg(frame))
    frame = frame_prevd(frame);
  pframe = frame_prev(frame);
  fn = frame_func(pframe);
  pc = debug_framepc(L, fn, frame);
  if (pc != NO_BCPOS) {
    GCproto *pt = funcproto(fn);
    const BCIns *ip = &proto_bc(pt)[check_exp(pc < pt->sizebc, pc)];
    MMS mm = bcmode_mm(bc_op(*ip));
    if (mm == MM_call) {
      BCReg slot = bc_a(*ip);
      if (bc_op(*ip) == BC_ITERC) slot -= 3;
      return lj_debug_slotname(pt, ip, slot, name);
    } else if (mm != MM__MAX) {
      *name = strdata(mmname_str(G(L), mm));
      return "metamethod";
    }
  }
  return NULL;
}