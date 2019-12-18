#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_19__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_21__ {int c; TYPE_1__* L; int /*<<< orphan*/  sb; } ;
struct TYPE_20__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_2__ TValue ;
typedef  scalar_t__ StrScanFmt ;
typedef  TYPE_3__ LexState ;
typedef  int LexChar ;
typedef  int /*<<< orphan*/  GCcdata ;

/* Variables and functions */
 int /*<<< orphan*/  CTID_COMPLEX_DOUBLE ; 
 int /*<<< orphan*/  CTID_INT64 ; 
 int /*<<< orphan*/  CTID_UINT64 ; 
 int /*<<< orphan*/  G (TYPE_1__*) ; 
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  LJ_ERR_XNUMBER ; 
 scalar_t__ LJ_HASFFI ; 
 int /*<<< orphan*/  LJ_TISNUM ; 
 scalar_t__ STRSCAN_ERROR ; 
 scalar_t__ STRSCAN_I64 ; 
 scalar_t__ STRSCAN_IMAG ; 
 scalar_t__ STRSCAN_INT ; 
 scalar_t__ STRSCAN_NUM ; 
 int STRSCAN_OPT_IMAG ; 
 int STRSCAN_OPT_LL ; 
 int STRSCAN_OPT_TOINT ; 
 int STRSCAN_OPT_TONUM ; 
 scalar_t__ STRSCAN_U64 ; 
 int /*<<< orphan*/  TK_number ; 
 scalar_t__ cdataptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctype_ctsG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lex_save (TYPE_3__*,char) ; 
 int lex_savenext (TYPE_3__*) ; 
 int /*<<< orphan*/ * lj_cdata_new_ (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int lj_char_isdigit (int) ; 
 scalar_t__ lj_char_isident (int) ; 
 int /*<<< orphan*/  lj_lex_error (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_parse_keepcdata (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lj_strscan_scan (int /*<<< orphan*/  const*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  luaopen_ffi (TYPE_1__*) ; 
 double numV (TYPE_2__*) ; 
 int /*<<< orphan*/  restorestack (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savestack (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sbufB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setitype (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lex_number(LexState *ls, TValue *tv)
{
  StrScanFmt fmt;
  LexChar c, xp = 'e';
  lua_assert(lj_char_isdigit(ls->c));
  if ((c = ls->c) == '0' && (lex_savenext(ls) | 0x20) == 'x')
    xp = 'p';
  while (lj_char_isident(ls->c) || ls->c == '.' ||
	 ((ls->c == '-' || ls->c == '+') && (c | 0x20) == xp)) {
    c = ls->c;
    lex_savenext(ls);
  }
  lex_save(ls, '\0');
  fmt = lj_strscan_scan((const uint8_t *)sbufB(&ls->sb), tv,
	  (LJ_DUALNUM ? STRSCAN_OPT_TOINT : STRSCAN_OPT_TONUM) |
	  (LJ_HASFFI ? (STRSCAN_OPT_LL|STRSCAN_OPT_IMAG) : 0));
  if (LJ_DUALNUM && fmt == STRSCAN_INT) {
    setitype(tv, LJ_TISNUM);
  } else if (fmt == STRSCAN_NUM) {
    /* Already in correct format. */
#if LJ_HASFFI
  } else if (fmt != STRSCAN_ERROR) {
    lua_State *L = ls->L;
    GCcdata *cd;
    lua_assert(fmt == STRSCAN_I64 || fmt == STRSCAN_U64 || fmt == STRSCAN_IMAG);
    if (!ctype_ctsG(G(L))) {
      ptrdiff_t oldtop = savestack(L, L->top);
      luaopen_ffi(L);  /* Load FFI library on-demand. */
      L->top = restorestack(L, oldtop);
    }
    if (fmt == STRSCAN_IMAG) {
      cd = lj_cdata_new_(L, CTID_COMPLEX_DOUBLE, 2*sizeof(double));
      ((double *)cdataptr(cd))[0] = 0;
      ((double *)cdataptr(cd))[1] = numV(tv);
    } else {
      cd = lj_cdata_new_(L, fmt==STRSCAN_I64 ? CTID_INT64 : CTID_UINT64, 8);
      *(uint64_t *)cdataptr(cd) = tv->u64;
    }
    lj_parse_keepcdata(ls, tv, cd);
#endif
  } else {
    lua_assert(fmt == STRSCAN_ERROR);
    lj_lex_error(ls, TK_number, LJ_ERR_XNUMBER);
  }
}