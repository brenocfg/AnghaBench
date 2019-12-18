#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {void** base; } ;
typedef  TYPE_1__ jit_State ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_30__ {int info; int size; int sib; int /*<<< orphan*/  name; } ;
struct TYPE_29__ {TYPE_2__* argv; } ;
struct TYPE_28__ {scalar_t__ u64; } ;
typedef  TYPE_2__ TValue ;
typedef  void* TRef ;
typedef  TYPE_3__ RecordFFData ;
typedef  size_t MSize ;
typedef  int /*<<< orphan*/  GCcdata ;
typedef  int CTypeID ;
typedef  TYPE_4__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int CTSize ;
typedef  int CTInfo ;

/* Variables and functions */
 int CREC_FILL_MAXUNROLL ; 
 int CTF_VLA ; 
 int CTID_INT32 ; 
 scalar_t__ CT_MEMALIGN ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRTGI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRT_CDATA ; 
 int /*<<< orphan*/  IRT_PTR ; 
 int /*<<< orphan*/  IR_ADD ; 
 int /*<<< orphan*/  IR_ADDOV ; 
 int /*<<< orphan*/  IR_CNEW ; 
 int /*<<< orphan*/  IR_CNEWI ; 
 int /*<<< orphan*/  IR_MULOV ; 
 int /*<<< orphan*/  J2G (TYPE_1__*) ; 
 int /*<<< orphan*/  LJ_TRERR_NYICONV ; 
 int /*<<< orphan*/  MM_gc ; 
 void* TREF_NIL ; 
 void* crec_ct_tv (TYPE_1__*,TYPE_4__*,void*,void*,TYPE_2__*) ; 
 int /*<<< orphan*/  crec_fill (TYPE_1__*,void*,void*,void*,unsigned int) ; 
 int /*<<< orphan*/  crec_finalizer (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ctype_align (int) ; 
 int /*<<< orphan*/ * ctype_ctsG (int /*<<< orphan*/ ) ; 
 TYPE_4__* ctype_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ctype_isarray (int) ; 
 int /*<<< orphan*/  ctype_isconstval (int) ; 
 scalar_t__ ctype_isenum (int) ; 
 scalar_t__ ctype_isfield (int) ; 
 scalar_t__ ctype_isinteger (int) ; 
 scalar_t__ ctype_isnum (int) ; 
 scalar_t__ ctype_isptr (int) ; 
 scalar_t__ ctype_isstruct (int) ; 
 TYPE_4__* ctype_raw (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_4__*) ; 
 void* emitir (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_cconv_multi_init (int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*) ; 
 int lj_ctype_info (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/ * lj_ctype_meta (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lj_ctype_vlsize (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 void* lj_ir_kint (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_ir_kint64 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* lj_ir_kintp (TYPE_1__*,int) ; 
 void* lj_ir_kptr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* lj_needsplit (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setintV (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crec_alloc(jit_State *J, RecordFFData *rd, CTypeID id)
{
  CTState *cts = ctype_ctsG(J2G(J));
  CTSize sz;
  CTInfo info = lj_ctype_info(cts, id, &sz);
  CType *d = ctype_raw(cts, id);
  TRef trcd, trid = lj_ir_kint(J, id);
  cTValue *fin;
  /* Use special instruction to box pointer or 32/64 bit integer. */
  if (ctype_isptr(info) || (ctype_isinteger(info) && (sz == 4 || sz == 8))) {
    TRef sp = J->base[1] ? crec_ct_tv(J, d, 0, J->base[1], &rd->argv[1]) :
	      ctype_isptr(info) ? lj_ir_kptr(J, NULL) :
	      sz == 4 ? lj_ir_kint(J, 0) :
	      (lj_needsplit(J), lj_ir_kint64(J, 0));
    J->base[0] = emitir(IRTG(IR_CNEWI, IRT_CDATA), trid, sp);
    return;
  } else {
    TRef trsz = TREF_NIL;
    if ((info & CTF_VLA)) {  /* Calculate VLA/VLS size at runtime. */
      CTSize sz0, sz1;
      if (!J->base[1] || J->base[2])
	lj_trace_err(J, LJ_TRERR_NYICONV);  /* NYI: init VLA/VLS. */
      trsz = crec_ct_tv(J, ctype_get(cts, CTID_INT32), 0,
			J->base[1], &rd->argv[1]);
      sz0 = lj_ctype_vlsize(cts, d, 0);
      sz1 = lj_ctype_vlsize(cts, d, 1);
      trsz = emitir(IRTGI(IR_MULOV), trsz, lj_ir_kint(J, (int32_t)(sz1-sz0)));
      trsz = emitir(IRTGI(IR_ADDOV), trsz, lj_ir_kint(J, (int32_t)sz0));
      J->base[1] = 0;  /* Simplify logic below. */
    } else if (ctype_align(info) > CT_MEMALIGN) {
      trsz = lj_ir_kint(J, sz);
    }
    trcd = emitir(IRTG(IR_CNEW, IRT_CDATA), trid, trsz);
    if (sz > 128 || (info & CTF_VLA)) {
      TRef dp;
      CTSize align;
    special:  /* Only handle bulk zero-fill for large/VLA/VLS types. */
      if (J->base[1])
	lj_trace_err(J, LJ_TRERR_NYICONV);  /* NYI: init large/VLA/VLS types. */
      dp = emitir(IRT(IR_ADD, IRT_PTR), trcd, lj_ir_kintp(J, sizeof(GCcdata)));
      if (trsz == TREF_NIL) trsz = lj_ir_kint(J, sz);
      align = ctype_align(info);
      if (align < CT_MEMALIGN) align = CT_MEMALIGN;
      crec_fill(J, dp, trsz, lj_ir_kint(J, 0), (1u << align));
    } else if (J->base[1] && !J->base[2] &&
	!lj_cconv_multi_init(cts, d, &rd->argv[1])) {
      goto single_init;
    } else if (ctype_isarray(d->info)) {
      CType *dc = ctype_rawchild(cts, d);  /* Array element type. */
      CTSize ofs, esize = dc->size;
      TRef sp = 0;
      TValue tv;
      TValue *sval = &tv;
      MSize i;
      tv.u64 = 0;
      if (!(ctype_isnum(dc->info) || ctype_isptr(dc->info)) ||
	  esize * CREC_FILL_MAXUNROLL < sz)
	goto special;
      for (i = 1, ofs = 0; ofs < sz; ofs += esize) {
	TRef dp = emitir(IRT(IR_ADD, IRT_PTR), trcd,
			 lj_ir_kintp(J, ofs + sizeof(GCcdata)));
	if (J->base[i]) {
	  sp = J->base[i];
	  sval = &rd->argv[i];
	  i++;
	} else if (i != 2) {
	  sp = ctype_isnum(dc->info) ? lj_ir_kint(J, 0) : TREF_NIL;
	}
	crec_ct_tv(J, dc, dp, sp, sval);
      }
    } else if (ctype_isstruct(d->info)) {
      CTypeID fid = d->sib;
      MSize i = 1;
      while (fid) {
	CType *df = ctype_get(cts, fid);
	fid = df->sib;
	if (ctype_isfield(df->info)) {
	  CType *dc;
	  TRef sp, dp;
	  TValue tv;
	  TValue *sval = &tv;
	  setintV(&tv, 0);
	  if (!gcref(df->name)) continue;  /* Ignore unnamed fields. */
	  dc = ctype_rawchild(cts, df);  /* Field type. */
	  if (!(ctype_isnum(dc->info) || ctype_isptr(dc->info) ||
		ctype_isenum(dc->info)))
	    lj_trace_err(J, LJ_TRERR_NYICONV);  /* NYI: init aggregates. */
	  if (J->base[i]) {
	    sp = J->base[i];
	    sval = &rd->argv[i];
	    i++;
	  } else {
	    sp = ctype_isptr(dc->info) ? TREF_NIL : lj_ir_kint(J, 0);
	  }
	  dp = emitir(IRT(IR_ADD, IRT_PTR), trcd,
		      lj_ir_kintp(J, df->size + sizeof(GCcdata)));
	  crec_ct_tv(J, dc, dp, sp, sval);
	} else if (!ctype_isconstval(df->info)) {
	  /* NYI: init bitfields and sub-structures. */
	  lj_trace_err(J, LJ_TRERR_NYICONV);
	}
      }
    } else {
      TRef dp;
    single_init:
      dp = emitir(IRT(IR_ADD, IRT_PTR), trcd, lj_ir_kintp(J, sizeof(GCcdata)));
      if (J->base[1]) {
	crec_ct_tv(J, d, dp, J->base[1], &rd->argv[1]);
      } else {
	TValue tv;
	tv.u64 = 0;
	crec_ct_tv(J, d, dp, lj_ir_kint(J, 0), &tv);
      }
    }
  }
  J->base[0] = trcd;
  /* Handle __gc metamethod. */
  fin = lj_ctype_meta(cts, id, MM_gc);
  if (fin)
    crec_finalizer(J, trcd, 0, fin);
}