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
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_20__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_2__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_21__ {scalar_t__ len; } ;
struct TYPE_19__ {scalar_t__ total; scalar_t__ threshold; } ;
struct TYPE_18__ {TYPE_1__ gc; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  SBuf ;
typedef  scalar_t__ MSize ;
typedef  TYPE_3__ GCstr ;

/* Variables and functions */
 TYPE_16__* G (TYPE_2__*) ; 
 int /*<<< orphan*/  LJ_ERR_OPCAT ; 
 int /*<<< orphan*/  LJ_ERR_STROV ; 
 int LJ_FR2 ; 
 scalar_t__ LJ_MAX_STR ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 int /*<<< orphan*/  MM_concat ; 
 int /*<<< orphan*/  STRFMT_G14 ; 
 scalar_t__ STRFMT_MAXBUF_NUM ; 
 int /*<<< orphan*/  copyTV (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curr_topL (TYPE_2__*) ; 
 int /*<<< orphan*/  intV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_buf_more (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lj_buf_putmem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lj_buf_str (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_buf_tmp_ (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_cont_cat ; 
 int /*<<< orphan*/  lj_err_msg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_optype (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_gc_step (TYPE_2__*) ; 
 int /*<<< orphan*/ * lj_meta_lookup (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_strfmt_putfnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_strfmt_putint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setcont (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setstrV (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* strV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdata (TYPE_3__*) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnumber (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

TValue *lj_meta_cat(lua_State *L, TValue *top, int left)
{
  int fromc = 0;
  if (left < 0) { left = -left; fromc = 1; }
  do {
    if (!(tvisstr(top) || tvisnumber(top)) ||
	!(tvisstr(top-1) || tvisnumber(top-1))) {
      cTValue *mo = lj_meta_lookup(L, top-1, MM_concat);
      if (tvisnil(mo)) {
	mo = lj_meta_lookup(L, top, MM_concat);
	if (tvisnil(mo)) {
	  if (tvisstr(top-1) || tvisnumber(top-1)) top++;
	  lj_err_optype(L, top-1, LJ_ERR_OPCAT);
	  return NULL;  /* unreachable */
	}
      }
      /* One of the top two elements is not a string, call __cat metamethod:
      **
      ** before:    [...][CAT stack .........................]
      **                                 top-1     top         top+1 top+2
      ** pick two:  [...][CAT stack ...] [o1]      [o2]
      ** setup mm:  [...][CAT stack ...] [cont|?]  [mo|tmtype] [o1]  [o2]
      ** in asm:    [...][CAT stack ...] [cont|PC] [mo|delta]  [o1]  [o2]
      **            ^-- func base                              ^-- mm base
      ** after mm:  [...][CAT stack ...] <--push-- [result]
      ** next step: [...][CAT stack .............]
      */
      copyTV(L, top+2*LJ_FR2+2, top);  /* Carefully ordered stack copies! */
      copyTV(L, top+2*LJ_FR2+1, top-1);
      copyTV(L, top+LJ_FR2, mo);
      setcont(top-1, lj_cont_cat);
      if (LJ_FR2) { setnilV(top); setnilV(top+2); top += 2; }
      return top+1;  /* Trigger metamethod call. */
    } else {
      /* Pick as many strings as possible from the top and concatenate them:
      **
      ** before:    [...][CAT stack ...........................]
      ** pick str:  [...][CAT stack ...] [...... strings ......]
      ** concat:    [...][CAT stack ...] [result]
      ** next step: [...][CAT stack ............]
      */
      TValue *e, *o = top;
      uint64_t tlen = tvisstr(o) ? strV(o)->len : STRFMT_MAXBUF_NUM;
      SBuf *sb;
      do {
	o--; tlen += tvisstr(o) ? strV(o)->len : STRFMT_MAXBUF_NUM;
      } while (--left > 0 && (tvisstr(o-1) || tvisnumber(o-1)));
      if (tlen >= LJ_MAX_STR) lj_err_msg(L, LJ_ERR_STROV);
      sb = lj_buf_tmp_(L);
      lj_buf_more(sb, (MSize)tlen);
      for (e = top, top = o; o <= e; o++) {
	if (tvisstr(o)) {
	  GCstr *s = strV(o);
	  MSize len = s->len;
	  lj_buf_putmem(sb, strdata(s), len);
	} else if (tvisint(o)) {
	  lj_strfmt_putint(sb, intV(o));
	} else {
	  lj_strfmt_putfnum(sb, STRFMT_G14, numV(o));
	}
      }
      setstrV(L, top, lj_buf_str(L, sb));
    }
  } while (left >= 1);
  if (LJ_UNLIKELY(G(L)->gc.total >= G(L)->gc.threshold)) {
    if (!fromc) L->top = curr_topL(L);
    lj_gc_step(L);
  }
  return NULL;
}