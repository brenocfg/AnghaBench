#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__* base; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_15__ {int info; int size; scalar_t__ sib; } ;
struct TYPE_14__ {int /*<<< orphan*/ * argv; } ;
typedef  scalar_t__ TRef ;
typedef  TYPE_2__ RecordFFData ;
typedef  int MSize ;
typedef  scalar_t__ CTypeID ;
typedef  TYPE_3__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 int CCI_NARGS_MAX ; 
 scalar_t__ CTCC_FASTCALL ; 
 scalar_t__ CTCC_THISCALL ; 
 int CTF_UNSIGNED ; 
 int CTF_VARARG ; 
 int /*<<< orphan*/  IRCONV_SEXT ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_I16 ; 
 int /*<<< orphan*/  IRT_I64 ; 
 int /*<<< orphan*/  IRT_I8 ; 
 int /*<<< orphan*/  IRT_INT ; 
 int /*<<< orphan*/  IRT_NIL ; 
 int /*<<< orphan*/  IRT_U16 ; 
 int /*<<< orphan*/  IRT_U64 ; 
 int /*<<< orphan*/  IRT_U8 ; 
 int /*<<< orphan*/  IR_CARG ; 
 scalar_t__ LJ_SOFTFP ; 
 int /*<<< orphan*/  LJ_TRERR_NYICALL ; 
 scalar_t__ TREF_NIL ; 
 scalar_t__ crec_ct_tv (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ctype_cconv (int) ; 
 scalar_t__ ctype_cid (int) ; 
 TYPE_3__* ctype_get (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ctype_isattrib (int) ; 
 scalar_t__ ctype_isenum (int) ; 
 int /*<<< orphan*/  ctype_isfield (int) ; 
 scalar_t__ ctype_isfp (int) ; 
 scalar_t__ ctype_isinteger_or_bool (int) ; 
 scalar_t__ ctype_isnum (int) ; 
 scalar_t__ ctype_isptr (int) ; 
 TYPE_3__* ctype_raw (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ emitconv (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ emitir (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ lj_ccall_ctid_vararg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_needsplit (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ tref_typerange (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRef crec_call_args(jit_State *J, RecordFFData *rd,
			   CTState *cts, CType *ct)
{
  TRef args[CCI_NARGS_MAX];
  CTypeID fid;
  MSize i, n;
  TRef tr, *base;
  cTValue *o;
#if LJ_TARGET_X86
#if LJ_ABI_WIN
  TRef *arg0 = NULL, *arg1 = NULL;
#endif
  int ngpr = 0;
  if (ctype_cconv(ct->info) == CTCC_THISCALL)
    ngpr = 1;
  else if (ctype_cconv(ct->info) == CTCC_FASTCALL)
    ngpr = 2;
#endif

  /* Skip initial attributes. */
  fid = ct->sib;
  while (fid) {
    CType *ctf = ctype_get(cts, fid);
    if (!ctype_isattrib(ctf->info)) break;
    fid = ctf->sib;
  }
  args[0] = TREF_NIL;
  for (n = 0, base = J->base+1, o = rd->argv+1; *base; n++, base++, o++) {
    CTypeID did;
    CType *d;

    if (n >= CCI_NARGS_MAX)
      lj_trace_err(J, LJ_TRERR_NYICALL);

    if (fid) {  /* Get argument type from field. */
      CType *ctf = ctype_get(cts, fid);
      fid = ctf->sib;
      lua_assert(ctype_isfield(ctf->info));
      did = ctype_cid(ctf->info);
    } else {
      if (!(ct->info & CTF_VARARG))
	lj_trace_err(J, LJ_TRERR_NYICALL);  /* Too many arguments. */
      did = lj_ccall_ctid_vararg(cts, o);  /* Infer vararg type. */
    }
    d = ctype_raw(cts, did);
    if (!(ctype_isnum(d->info) || ctype_isptr(d->info) ||
	  ctype_isenum(d->info)))
      lj_trace_err(J, LJ_TRERR_NYICALL);
    tr = crec_ct_tv(J, d, 0, *base, o);
    if (ctype_isinteger_or_bool(d->info)) {
      if (d->size < 4) {
	if ((d->info & CTF_UNSIGNED))
	  tr = emitconv(tr, IRT_INT, d->size==1 ? IRT_U8 : IRT_U16, 0);
	else
	  tr = emitconv(tr, IRT_INT, d->size==1 ? IRT_I8 : IRT_I16,IRCONV_SEXT);
      }
    } else if (LJ_SOFTFP && ctype_isfp(d->info) && d->size > 4) {
      lj_needsplit(J);
    }
#if LJ_TARGET_X86
    /* 64 bit args must not end up in registers for fastcall/thiscall. */
#if LJ_ABI_WIN
    if (!ctype_isfp(d->info)) {
      /* Sigh, the Windows/x86 ABI allows reordering across 64 bit args. */
      if (tref_typerange(tr, IRT_I64, IRT_U64)) {
	if (ngpr) {
	  arg0 = &args[n]; args[n++] = TREF_NIL; ngpr--;
	  if (ngpr) {
	    arg1 = &args[n]; args[n++] = TREF_NIL; ngpr--;
	  }
	}
      } else {
	if (arg0) { *arg0 = tr; arg0 = NULL; n--; continue; }
	if (arg1) { *arg1 = tr; arg1 = NULL; n--; continue; }
	if (ngpr) ngpr--;
      }
    }
#else
    if (!ctype_isfp(d->info) && ngpr) {
      if (tref_typerange(tr, IRT_I64, IRT_U64)) {
	/* No reordering for other x86 ABIs. Simply add alignment args. */
	do { args[n++] = TREF_NIL; } while (--ngpr);
      } else {
	ngpr--;
      }
    }
#endif
#endif
    args[n] = tr;
  }
  tr = args[0];
  for (i = 1; i < n; i++)
    tr = emitir(IRT(IR_CARG, IRT_NIL), tr, args[i]);
  return tr;
}