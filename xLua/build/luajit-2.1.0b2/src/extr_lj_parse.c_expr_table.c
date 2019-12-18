#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_59__   TYPE_9__ ;
typedef  struct TYPE_58__   TYPE_8__ ;
typedef  struct TYPE_57__   TYPE_7__ ;
typedef  struct TYPE_56__   TYPE_6__ ;
typedef  struct TYPE_55__   TYPE_5__ ;
typedef  struct TYPE_54__   TYPE_4__ ;
typedef  struct TYPE_53__   TYPE_3__ ;
typedef  struct TYPE_52__   TYPE_2__ ;
typedef  struct TYPE_51__   TYPE_1__ ;
typedef  struct TYPE_50__   TYPE_12__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_59__ {void* ins; } ;
struct TYPE_51__ {size_t info; } ;
struct TYPE_52__ {int lo; int hi; } ;
struct TYPE_50__ {TYPE_2__ u32; } ;
struct TYPE_53__ {TYPE_1__ s; TYPE_12__ nval; } ;
struct TYPE_58__ {scalar_t__ k; TYPE_3__ u; } ;
struct TYPE_57__ {scalar_t__ freereg; int pc; int /*<<< orphan*/  L; TYPE_9__* bcbase; } ;
struct TYPE_56__ {int asize; int hmask; int /*<<< orphan*/  node; } ;
struct TYPE_55__ {char tok; int /*<<< orphan*/  linenumber; TYPE_7__* fs; } ;
struct TYPE_54__ {int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_4__ Node ;
typedef  TYPE_5__ LexState ;
typedef  TYPE_6__ GCtab ;
typedef  TYPE_7__ FuncState ;
typedef  TYPE_8__ ExpDesc ;
typedef  scalar_t__ BCReg ;
typedef  size_t BCPos ;
typedef  int /*<<< orphan*/  BCLine ;
typedef  TYPE_9__ BCInsLine ;
typedef  void* BCIns ;

/* Variables and functions */
 void* BCINS_AD (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BC_TDUP ; 
 int /*<<< orphan*/  BC_TNEW ; 
 scalar_t__ BC_TSETB ; 
 int /*<<< orphan*/  BC_TSETM ; 
 scalar_t__ BC_TSETV ; 
 int /*<<< orphan*/  LJ_52 ; 
 int /*<<< orphan*/  LJ_TTAB ; 
 char TK_goto ; 
 char TK_name ; 
 scalar_t__ VCALL ; 
 scalar_t__ VKNIL ; 
 scalar_t__ VKNUM ; 
 scalar_t__ VKSTR ; 
 scalar_t__ VNONRELOC ; 
 scalar_t__ VRELOCABLE ; 
 scalar_t__ bc_a (void*) ; 
 scalar_t__ bc_op (void*) ; 
 size_t bcemit_AD (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcemit_store (TYPE_7__*,TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  bcreg_reserve (TYPE_7__*,int) ; 
 scalar_t__ const_gc (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ const_num (TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  expr (TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  expr_bracket (TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  expr_index (TYPE_7__*,TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  expr_init (TYPE_8__*,scalar_t__,scalar_t__) ; 
 scalar_t__ expr_isk (TYPE_8__*) ; 
 scalar_t__ expr_isk_nojump (TYPE_8__*) ; 
 scalar_t__ expr_isnumk (TYPE_8__*) ; 
 int /*<<< orphan*/  expr_kvalue (int /*<<< orphan*/ *,TYPE_8__*) ; 
 scalar_t__ expr_numiszero (TYPE_8__*) ; 
 int /*<<< orphan*/  expr_str (TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  expr_toanyreg (TYPE_7__*,TYPE_8__*) ; 
 int hsize2hbits (int) ; 
 int /*<<< orphan*/  lex_check (TYPE_5__*,char) ; 
 int /*<<< orphan*/  lex_match (TYPE_5__*,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lex_opt (TYPE_5__*,char) ; 
 int /*<<< orphan*/  lj_gc_anybarriert (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  lj_gc_check (int /*<<< orphan*/ ) ; 
 char lj_lex_lookahead (TYPE_5__*) ; 
 TYPE_6__* lj_tab_new (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lj_tab_reasize (int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int /*<<< orphan*/ * lj_tab_set (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 TYPE_4__* noderef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj2gco (TYPE_6__*) ; 
 int /*<<< orphan*/  setbc_b (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbc_d (void**,int) ; 
 int /*<<< orphan*/  setintV (TYPE_12__*,int) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  settabV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__*) ; 
 TYPE_6__* tabV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvistab (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void expr_table(LexState *ls, ExpDesc *e)
{
  FuncState *fs = ls->fs;
  BCLine line = ls->linenumber;
  GCtab *t = NULL;
  int vcall = 0, needarr = 0, fixt = 0;
  uint32_t narr = 1;  /* First array index. */
  uint32_t nhash = 0;  /* Number of hash entries. */
  BCReg freg = fs->freereg;
  BCPos pc = bcemit_AD(fs, BC_TNEW, freg, 0);
  expr_init(e, VNONRELOC, freg);
  bcreg_reserve(fs, 1);
  freg++;
  lex_check(ls, '{');
  while (ls->tok != '}') {
    ExpDesc key, val;
    vcall = 0;
    if (ls->tok == '[') {
      expr_bracket(ls, &key);  /* Already calls expr_toval. */
      if (!expr_isk(&key)) expr_index(fs, e, &key);
      if (expr_isnumk(&key) && expr_numiszero(&key)) needarr = 1; else nhash++;
      lex_check(ls, '=');
    } else if ((ls->tok == TK_name || (!LJ_52 && ls->tok == TK_goto)) &&
	       lj_lex_lookahead(ls) == '=') {
      expr_str(ls, &key);
      lex_check(ls, '=');
      nhash++;
    } else {
      expr_init(&key, VKNUM, 0);
      setintV(&key.u.nval, (int)narr);
      narr++;
      needarr = vcall = 1;
    }
    expr(ls, &val);
    if (expr_isk(&key) && key.k != VKNIL &&
	(key.k == VKSTR || expr_isk_nojump(&val))) {
      TValue k, *v;
      if (!t) {  /* Create template table on demand. */
	BCReg kidx;
	t = lj_tab_new(fs->L, needarr ? narr : 0, hsize2hbits(nhash));
	kidx = const_gc(fs, obj2gco(t), LJ_TTAB);
	fs->bcbase[pc].ins = BCINS_AD(BC_TDUP, freg-1, kidx);
      }
      vcall = 0;
      expr_kvalue(&k, &key);
      v = lj_tab_set(fs->L, t, &k);
      lj_gc_anybarriert(fs->L, t);
      if (expr_isk_nojump(&val)) {  /* Add const key/value to template table. */
	expr_kvalue(v, &val);
      } else {  /* Otherwise create dummy string key (avoids lj_tab_newkey). */
	settabV(fs->L, v, t);  /* Preserve key with table itself as value. */
	fixt = 1;   /* Fix this later, after all resizes. */
	goto nonconst;
      }
    } else {
    nonconst:
      if (val.k != VCALL) { expr_toanyreg(fs, &val); vcall = 0; }
      if (expr_isk(&key)) expr_index(fs, e, &key);
      bcemit_store(fs, e, &val);
    }
    fs->freereg = freg;
    if (!lex_opt(ls, ',') && !lex_opt(ls, ';')) break;
  }
  lex_match(ls, '}', '{', line);
  if (vcall) {
    BCInsLine *ilp = &fs->bcbase[fs->pc-1];
    ExpDesc en;
    lua_assert(bc_a(ilp->ins) == freg &&
	       bc_op(ilp->ins) == (narr > 256 ? BC_TSETV : BC_TSETB));
    expr_init(&en, VKNUM, 0);
    en.u.nval.u32.lo = narr-1;
    en.u.nval.u32.hi = 0x43300000;  /* Biased integer to avoid denormals. */
    if (narr > 256) { fs->pc--; ilp--; }
    ilp->ins = BCINS_AD(BC_TSETM, freg, const_num(fs, &en));
    setbc_b(&ilp[-1].ins, 0);
  }
  if (pc == fs->pc-1) {  /* Make expr relocable if possible. */
    e->u.s.info = pc;
    fs->freereg--;
    e->k = VRELOCABLE;
  } else {
    e->k = VNONRELOC;  /* May have been changed by expr_index. */
  }
  if (!t) {  /* Construct TNEW RD: hhhhhaaaaaaaaaaa. */
    BCIns *ip = &fs->bcbase[pc].ins;
    if (!needarr) narr = 0;
    else if (narr < 3) narr = 3;
    else if (narr > 0x7ff) narr = 0x7ff;
    setbc_d(ip, narr|(hsize2hbits(nhash)<<11));
  } else {
    if (needarr && t->asize < narr)
      lj_tab_reasize(fs->L, t, narr-1);
    if (fixt) {  /* Fix value for dummy keys in template table. */
      Node *node = noderef(t->node);
      uint32_t i, hmask = t->hmask;
      for (i = 0; i <= hmask; i++) {
	Node *n = &node[i];
	if (tvistab(&n->val)) {
	  lua_assert(tabV(&n->val) == t);
	  setnilV(&n->val);  /* Turn value into nil. */
	}
      }
    }
    lj_gc_check(fs->L);
  }
}