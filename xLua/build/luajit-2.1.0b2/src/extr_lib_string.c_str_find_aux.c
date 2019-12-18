#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ top; scalar_t__ base; } ;
typedef  TYPE_1__ lua_State ;
typedef  scalar_t__ int32_t ;
struct TYPE_14__ {scalar_t__ len; } ;
struct TYPE_13__ {char const* src_init; char const* src_end; scalar_t__ depth; scalar_t__ level; TYPE_1__* L; } ;
typedef  TYPE_2__ MatchState ;
typedef  scalar_t__ MSize ;
typedef  TYPE_3__ GCstr ;

/* Variables and functions */
 TYPE_3__* lj_lib_checkstr (TYPE_1__*,int) ; 
 scalar_t__ lj_lib_optint (TYPE_1__*,int,int) ; 
 char* lj_str_find (char const*,char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lj_str_haspattern (TYPE_3__*) ; 
 char* match (TYPE_2__*,char const*,char const*) ; 
 int push_captures (TYPE_2__*,char const*,char const*) ; 
 int /*<<< orphan*/  setintV (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  setnilV (scalar_t__) ; 
 char const* strdata (TYPE_3__*) ; 
 scalar_t__ tvistruecond (scalar_t__) ; 

__attribute__((used)) static int str_find_aux(lua_State *L, int find)
{
  GCstr *s = lj_lib_checkstr(L, 1);
  GCstr *p = lj_lib_checkstr(L, 2);
  int32_t start = lj_lib_optint(L, 3, 1);
  MSize st;
  if (start < 0) start += (int32_t)s->len; else start--;
  if (start < 0) start = 0;
  st = (MSize)start;
  if (st > s->len) {
#if LJ_52
    setnilV(L->top-1);
    return 1;
#else
    st = s->len;
#endif
  }
  if (find && ((L->base+3 < L->top && tvistruecond(L->base+3)) ||
	       !lj_str_haspattern(p))) {  /* Search for fixed string. */
    const char *q = lj_str_find(strdata(s)+st, strdata(p), s->len-st, p->len);
    if (q) {
      setintV(L->top-2, (int32_t)(q-strdata(s)) + 1);
      setintV(L->top-1, (int32_t)(q-strdata(s)) + (int32_t)p->len);
      return 2;
    }
  } else {  /* Search for pattern. */
    MatchState ms;
    const char *pstr = strdata(p);
    const char *sstr = strdata(s) + st;
    int anchor = 0;
    if (*pstr == '^') { pstr++; anchor = 1; }
    ms.L = L;
    ms.src_init = strdata(s);
    ms.src_end = strdata(s) + s->len;
    do {  /* Loop through string and try to match the pattern. */
      const char *q;
      ms.level = ms.depth = 0;
      q = match(&ms, sstr, pstr);
      if (q) {
	if (find) {
	  setintV(L->top++, (int32_t)(sstr-(strdata(s)-1)));
	  setintV(L->top++, (int32_t)(q-strdata(s)));
	  return push_captures(&ms, NULL, NULL) + 2;
	} else {
	  return push_captures(&ms, sstr, q);
	}
      }
    } while (sstr++ < ms.src_end && !anchor);
  }
  setnilV(L->top-1);  /* Not found. */
  return 1;
}