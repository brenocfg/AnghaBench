#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_11__ {int ffid; } ;
struct TYPE_13__ {TYPE_1__ c; } ;
struct TYPE_12__ {scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  TYPE_2__ GCproto ;
typedef  TYPE_3__ GCfunc ;

/* Variables and functions */
#define  FF_coroutine_wrap_aux 129 
#define  FF_string_gmatch_aux 128 
 int /*<<< orphan*/  IRFL_FUNC_FFID ; 
 int /*<<< orphan*/  IRFL_FUNC_PC ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_FUNC ; 
 int /*<<< orphan*/  IRT_INT ; 
 int /*<<< orphan*/  IRT_PGC ; 
 int /*<<< orphan*/  IRT_PROTO ; 
 int /*<<< orphan*/  IRT_U8 ; 
 int /*<<< orphan*/  IR_EQ ; 
 int /*<<< orphan*/  IR_FLOAD ; 
 scalar_t__ PROTO_CLC_POLY ; 
 int /*<<< orphan*/  emitir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* funcproto (TYPE_3__*) ; 
 scalar_t__ isluafunc (TYPE_3__*) ; 
 int /*<<< orphan*/  lj_ir_kfunc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  lj_ir_kgc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lj_ir_kptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj2gco (TYPE_2__*) ; 
 int /*<<< orphan*/  proto_bc (TYPE_2__*) ; 

__attribute__((used)) static TRef rec_call_specialize(jit_State *J, GCfunc *fn, TRef tr)
{
  TRef kfunc;
  if (isluafunc(fn)) {
    GCproto *pt = funcproto(fn);
    /* Too many closures created? Probably not a monomorphic function. */
    if (pt->flags >= PROTO_CLC_POLY) {  /* Specialize to prototype instead. */
      TRef trpt = emitir(IRT(IR_FLOAD, IRT_PGC), tr, IRFL_FUNC_PC);
      emitir(IRTG(IR_EQ, IRT_PGC), trpt, lj_ir_kptr(J, proto_bc(pt)));
      (void)lj_ir_kgc(J, obj2gco(pt), IRT_PROTO);  /* Prevent GC of proto. */
      return tr;
    }
  } else {
    /* Don't specialize to non-monomorphic builtins. */
    switch (fn->c.ffid) {
    case FF_coroutine_wrap_aux:
    case FF_string_gmatch_aux:
      /* NYI: io_file_iter doesn't have an ffid, yet. */
      {  /* Specialize to the ffid. */
	TRef trid = emitir(IRT(IR_FLOAD, IRT_U8), tr, IRFL_FUNC_FFID);
	emitir(IRTG(IR_EQ, IRT_INT), trid, lj_ir_kint(J, fn->c.ffid));
      }
      return tr;
    default:
      /* NYI: don't specialize to non-monomorphic C functions. */
      break;
    }
  }
  /* Otherwise specialize to the function (closure) value itself. */
  kfunc = lj_ir_kfunc(J, fn);
  emitir(IRTG(IR_EQ, IRT_FUNC), tr, kfunc);
  return kfunc;
}