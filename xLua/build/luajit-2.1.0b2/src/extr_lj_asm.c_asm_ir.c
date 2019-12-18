#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_137__   TYPE_5__ ;
typedef  struct TYPE_136__   TYPE_2__ ;
typedef  struct TYPE_135__   TYPE_1__ ;

/* Type definitions */
struct TYPE_137__ {int /*<<< orphan*/  errinfo; } ;
struct TYPE_136__ {TYPE_5__* J; int /*<<< orphan*/  gcsteps; int /*<<< orphan*/  curins; } ;
struct TYPE_135__ {int o; int /*<<< orphan*/  op1; int /*<<< orphan*/  t; } ;
typedef  int /*<<< orphan*/  IROp ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
#define  IR_ABC 215 
#define  IR_ABS 214 
#define  IR_ADD 213 
#define  IR_ADDOV 212 
#define  IR_ALOAD 211 
#define  IR_AREF 210 
#define  IR_ASTORE 209 
#define  IR_ATAN2 208 
#define  IR_BAND 207 
#define  IR_BNOT 206 
#define  IR_BOR 205 
#define  IR_BROL 204 
#define  IR_BROR 203 
#define  IR_BSAR 202 
#define  IR_BSHL 201 
#define  IR_BSHR 200 
#define  IR_BSWAP 199 
#define  IR_BUFHDR 198 
#define  IR_BUFPUT 197 
#define  IR_BUFSTR 196 
#define  IR_BXOR 195 
#define  IR_CALLA 194 
#define  IR_CALLL 193 
#define  IR_CALLN 192 
#define  IR_CALLS 191 
#define  IR_CALLXS 190 
#define  IR_CARG 189 
#define  IR_CNEW 188 
#define  IR_CNEWI 187 
#define  IR_CONV 186 
#define  IR_DIV 185 
#define  IR_EQ 184 
#define  IR_FLOAD 183 
#define  IR_FPMATH 182 
#define  IR_FREF 181 
#define  IR_FSTORE 180 
#define  IR_GCSTEP 179 
#define  IR_GE 178 
#define  IR_GT 177 
#define  IR_HIOP 176 
#define  IR_HLOAD 175 
#define  IR_HREF 174 
#define  IR_HREFK 173 
#define  IR_HSTORE 172 
#define  IR_LDEXP 171 
#define  IR_LE 170 
#define  IR_LOOP 169 
#define  IR_LREF 168 
#define  IR_LT 167 
#define  IR_MAX 166 
#define  IR_MIN 165 
#define  IR_MOD 164 
#define  IR_MUL 163 
#define  IR_MULOV 162 
#define  IR_NE 161 
#define  IR_NEG 160 
#define  IR_NEWREF 159 
#define  IR_NOP 158 
#define  IR_OBAR 157 
#define  IR_PHI 156 
#define  IR_POW 155 
#define  IR_PROF 154 
#define  IR_RETF 153 
#define  IR_SLOAD 152 
#define  IR_SNEW 151 
#define  IR_STRREF 150 
#define  IR_STRTO 149 
#define  IR_SUB 148 
#define  IR_SUBOV 147 
#define  IR_TBAR 146 
#define  IR_TDUP 145 
#define  IR_TNEW 144 
#define  IR_TOBIT 143 
#define  IR_TOSTR 142 
#define  IR_UGE 141 
#define  IR_UGT 140 
#define  IR_ULE 139 
#define  IR_ULOAD 138 
#define  IR_ULT 137 
#define  IR_UREFC 136 
#define  IR_UREFO 135 
#define  IR_USE 134 
#define  IR_USTORE 133 
#define  IR_VLOAD 132 
#define  IR_XBAR 131 
#define  IR_XLOAD 130 
#define  IR_XSNEW 129 
#define  IR_XSTORE 128 
 int /*<<< orphan*/  LJ_TRERR_NYIIR ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  asm_abs (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_add (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_addov (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_ahustore (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_ahuvload (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_aref (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_atan2 (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_band (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bnot (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bor (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_brol (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bror (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bsar (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bshl (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bshr (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bswap (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bufhdr (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bufput (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bufstr (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_bxor (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_call (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_callx (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_cnew (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_comp (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_conv (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_div (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_equal (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_fload (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_fpmath (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_fref (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_fstore (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_gcstep (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_hiop (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_href (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_hrefk (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_ldexp (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_loop (TYPE_2__*) ; 
 int /*<<< orphan*/  asm_lref (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_max (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_min (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_mod (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_mul (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_mulov (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_neg (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_newref (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_obar (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_phi (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_pow (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_prof (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_retf (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_sload (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_snew (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_strref (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_strto (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_sub (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_subov (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_tbar (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_tdup (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_tnew (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_tobit (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_tostr (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_uref (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_xload (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  asm_xstore (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  irt_isfp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_trace_err_info (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  ra_alloc1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_used (TYPE_1__*) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void asm_ir(ASMState *as, IRIns *ir)
{
  switch ((IROp)ir->o) {
  /* Miscellaneous ops. */
  case IR_LOOP: asm_loop(as); break;
  case IR_NOP: case IR_XBAR: lua_assert(!ra_used(ir)); break;
  case IR_USE:
    ra_alloc1(as, ir->op1, irt_isfp(ir->t) ? RSET_FPR : RSET_GPR); break;
  case IR_PHI: asm_phi(as, ir); break;
  case IR_HIOP: asm_hiop(as, ir); break;
  case IR_GCSTEP: asm_gcstep(as, ir); break;
  case IR_PROF: asm_prof(as, ir); break;

  /* Guarded assertions. */
  case IR_LT: case IR_GE: case IR_LE: case IR_GT:
  case IR_ULT: case IR_UGE: case IR_ULE: case IR_UGT:
  case IR_ABC:
    asm_comp(as, ir);
    break;
  case IR_EQ: case IR_NE:
    if ((ir-1)->o == IR_HREF && ir->op1 == as->curins-1) {
      as->curins--;
      asm_href(as, ir-1, (IROp)ir->o);
    } else {
      asm_equal(as, ir);
    }
    break;

  case IR_RETF: asm_retf(as, ir); break;

  /* Bit ops. */
  case IR_BNOT: asm_bnot(as, ir); break;
  case IR_BSWAP: asm_bswap(as, ir); break;
  case IR_BAND: asm_band(as, ir); break;
  case IR_BOR: asm_bor(as, ir); break;
  case IR_BXOR: asm_bxor(as, ir); break;
  case IR_BSHL: asm_bshl(as, ir); break;
  case IR_BSHR: asm_bshr(as, ir); break;
  case IR_BSAR: asm_bsar(as, ir); break;
  case IR_BROL: asm_brol(as, ir); break;
  case IR_BROR: asm_bror(as, ir); break;

  /* Arithmetic ops. */
  case IR_ADD: asm_add(as, ir); break;
  case IR_SUB: asm_sub(as, ir); break;
  case IR_MUL: asm_mul(as, ir); break;
  case IR_MOD: asm_mod(as, ir); break;
  case IR_NEG: asm_neg(as, ir); break;
#if LJ_SOFTFP
  case IR_DIV: case IR_POW: case IR_ABS:
  case IR_ATAN2: case IR_LDEXP: case IR_FPMATH: case IR_TOBIT:
    lua_assert(0);  /* Unused for LJ_SOFTFP. */
    break;
#else
  case IR_DIV: asm_div(as, ir); break;
  case IR_POW: asm_pow(as, ir); break;
  case IR_ABS: asm_abs(as, ir); break;
  case IR_ATAN2: asm_atan2(as, ir); break;
  case IR_LDEXP: asm_ldexp(as, ir); break;
  case IR_FPMATH: asm_fpmath(as, ir); break;
  case IR_TOBIT: asm_tobit(as, ir); break;
#endif
  case IR_MIN: asm_min(as, ir); break;
  case IR_MAX: asm_max(as, ir); break;

  /* Overflow-checking arithmetic ops. */
  case IR_ADDOV: asm_addov(as, ir); break;
  case IR_SUBOV: asm_subov(as, ir); break;
  case IR_MULOV: asm_mulov(as, ir); break;

  /* Memory references. */
  case IR_AREF: asm_aref(as, ir); break;
  case IR_HREF: asm_href(as, ir, 0); break;
  case IR_HREFK: asm_hrefk(as, ir); break;
  case IR_NEWREF: asm_newref(as, ir); break;
  case IR_UREFO: case IR_UREFC: asm_uref(as, ir); break;
  case IR_FREF: asm_fref(as, ir); break;
  case IR_STRREF: asm_strref(as, ir); break;
  case IR_LREF: asm_lref(as, ir); break;

  /* Loads and stores. */
  case IR_ALOAD: case IR_HLOAD: case IR_ULOAD: case IR_VLOAD:
    asm_ahuvload(as, ir);
    break;
  case IR_FLOAD: asm_fload(as, ir); break;
  case IR_XLOAD: asm_xload(as, ir); break;
  case IR_SLOAD: asm_sload(as, ir); break;

  case IR_ASTORE: case IR_HSTORE: case IR_USTORE: asm_ahustore(as, ir); break;
  case IR_FSTORE: asm_fstore(as, ir); break;
  case IR_XSTORE: asm_xstore(as, ir); break;

  /* Allocations. */
  case IR_SNEW: case IR_XSNEW: asm_snew(as, ir); break;
  case IR_TNEW: asm_tnew(as, ir); break;
  case IR_TDUP: asm_tdup(as, ir); break;
  case IR_CNEW: case IR_CNEWI: asm_cnew(as, ir); break;

  /* Buffer operations. */
  case IR_BUFHDR: asm_bufhdr(as, ir); break;
  case IR_BUFPUT: asm_bufput(as, ir); break;
  case IR_BUFSTR: asm_bufstr(as, ir); break;

  /* Write barriers. */
  case IR_TBAR: asm_tbar(as, ir); break;
  case IR_OBAR: asm_obar(as, ir); break;

  /* Type conversions. */
  case IR_CONV: asm_conv(as, ir); break;
  case IR_TOSTR: asm_tostr(as, ir); break;
  case IR_STRTO: asm_strto(as, ir); break;

  /* Calls. */
  case IR_CALLA:
    as->gcsteps++;
    /* fallthrough */
  case IR_CALLN: case IR_CALLL: case IR_CALLS: asm_call(as, ir); break;
  case IR_CALLXS: asm_callx(as, ir); break;
  case IR_CARG: break;

  default:
    setintV(&as->J->errinfo, ir->o);
    lj_trace_err_info(as->J, LJ_TRERR_NYIIR);
    break;
  }
}