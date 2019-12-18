#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {int /*<<< orphan*/  u64; } ;
struct TYPE_10__ {int /*<<< orphan*/  n; } ;
struct TYPE_9__ {int o; int /*<<< orphan*/  t; int /*<<< orphan*/  i; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  GCcdata ;

/* Variables and functions */
 int /*<<< orphan*/  CTID_INT64 ; 
#define  IR_KGC 135 
#define  IR_KINT 134 
#define  IR_KINT64 133 
#define  IR_KKPTR 132 
#define  IR_KNULL 131 
#define  IR_KNUM 130 
#define  IR_KPRI 129 
#define  IR_KPTR 128 
 int IR_KSLOT ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ cdataptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ir_kgc (TYPE_1__ const*) ; 
 TYPE_6__* ir_kint64 (TYPE_1__ const*) ; 
 TYPE_4__* ir_knum (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * ir_kptr (TYPE_1__ const*) ; 
 int /*<<< orphan*/  irt_toitype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_cdata_new_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setcdataV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgcV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlightudV (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnumV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpriV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lj_ir_kvalue(lua_State *L, TValue *tv, const IRIns *ir)
{
  UNUSED(L);
  lua_assert(ir->o != IR_KSLOT);  /* Common mistake. */
  switch (ir->o) {
  case IR_KPRI: setpriV(tv, irt_toitype(ir->t)); break;
  case IR_KINT: setintV(tv, ir->i); break;
  case IR_KGC: setgcV(L, tv, ir_kgc(ir), irt_toitype(ir->t)); break;
  case IR_KPTR: case IR_KKPTR: setlightudV(tv, ir_kptr(ir)); break;
  case IR_KNULL: setlightudV(tv, NULL); break;
  case IR_KNUM: setnumV(tv, ir_knum(ir)->n); break;
#if LJ_HASFFI
  case IR_KINT64: {
    GCcdata *cd = lj_cdata_new_(L, CTID_INT64, 8);
    *(uint64_t *)cdataptr(cd) = ir_kint64(ir)->u64;
    setcdataV(L, tv, cd);
    break;
    }
#endif
  default: lua_assert(0); break;
  }
}