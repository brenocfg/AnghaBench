#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ jit_State ;
typedef  int int32_t ;
struct TYPE_10__ {int /*<<< orphan*/ * gcroot; } ;
typedef  int /*<<< orphan*/  TRef ;

/* Variables and functions */
 int /*<<< orphan*/  IRFL_UDATA_FILE ; 
 int /*<<< orphan*/  IRFL_UDATA_UDTYPE ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_PTR ; 
 int /*<<< orphan*/  IRT_U8 ; 
 int /*<<< orphan*/  IRT_UDATA ; 
 int /*<<< orphan*/  IR_EQ ; 
 int /*<<< orphan*/  IR_FLOAD ; 
 int /*<<< orphan*/  IR_NE ; 
 int /*<<< orphan*/  IR_XLOAD ; 
 TYPE_7__* J2G (TYPE_1__*) ; 
 int /*<<< orphan*/  LJ_TRERR_BADTYPE ; 
 int /*<<< orphan*/  UDTYPE_IO_FILE ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_knull (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kptr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tref_isudata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRef recff_io_fp(jit_State *J, TRef *udp, int32_t id)
{
  TRef tr, ud, fp;
  if (id) {  /* io.func() */
    tr = lj_ir_kptr(J, &J2G(J)->gcroot[id]);
    ud = emitir(IRT(IR_XLOAD, IRT_UDATA), tr, 0);
  } else {  /* fp:method() */
    ud = J->base[0];
    if (!tref_isudata(ud))
      lj_trace_err(J, LJ_TRERR_BADTYPE);
    tr = emitir(IRT(IR_FLOAD, IRT_U8), ud, IRFL_UDATA_UDTYPE);
    emitir(IRTGI(IR_EQ), tr, lj_ir_kint(J, UDTYPE_IO_FILE));
  }
  *udp = ud;
  fp = emitir(IRT(IR_FLOAD, IRT_PTR), ud, IRFL_UDATA_FILE);
  emitir(IRTG(IR_NE, IRT_PTR), fp, lj_ir_knull(J, IRT_PTR));
  return fp;
}