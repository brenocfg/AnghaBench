#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_26__ {int /*<<< orphan*/ * top; int /*<<< orphan*/  maxstack; int /*<<< orphan*/  stack; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_27__ {char* source; char* short_src; int linedefined; int lastlinedefined; char* what; int currentline; int isvararg; char* namewhat; int /*<<< orphan*/ * name; scalar_t__ nparams; int /*<<< orphan*/  nups; scalar_t__ i_ci; } ;
typedef  TYPE_3__ lj_Debug ;
struct TYPE_25__ {int /*<<< orphan*/  nupvalues; int /*<<< orphan*/  gct; } ;
struct TYPE_29__ {TYPE_1__ c; } ;
struct TYPE_28__ {int firstline; int numline; int flags; size_t sizebc; scalar_t__ numparams; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  size_t MSize ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_4__ GCproto ;
typedef  TYPE_5__ GCfunc ;
typedef  int BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_TFUNC ; 
 int PROTO_VARARG ; 
 int /*<<< orphan*/  api_check (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int debug_frameline (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* frame_func (int /*<<< orphan*/ *) ; 
 TYPE_5__* funcV (int /*<<< orphan*/ *) ; 
 TYPE_4__* funcproto (TYPE_5__*) ; 
 int /*<<< orphan*/  incr_top (TYPE_2__*) ; 
 scalar_t__ isluafunc (TYPE_5__*) ; 
 char* lj_debug_funcname (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lj_debug_shortname (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lj_tab_new (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_tab_setint (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/ * proto_chunkname (TYPE_4__*) ; 
 void* proto_lineinfo (TYPE_4__*) ; 
 int /*<<< orphan*/  setboolV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setfuncV (TYPE_2__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  settabV (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* strdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisfunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

int lj_debug_getinfo(lua_State *L, const char *what, lj_Debug *ar, int ext)
{
  int opt_f = 0, opt_L = 0;
  TValue *frame = NULL;
  TValue *nextframe = NULL;
  GCfunc *fn;
  if (*what == '>') {
    TValue *func = L->top - 1;
    api_check(L, tvisfunc(func));
    fn = funcV(func);
    L->top--;
    what++;
  } else {
    uint32_t offset = (uint32_t)ar->i_ci & 0xffff;
    uint32_t size = (uint32_t)ar->i_ci >> 16;
    lua_assert(offset != 0);
    frame = tvref(L->stack) + offset;
    if (size) nextframe = frame + size;
    lua_assert(frame <= tvref(L->maxstack) &&
	       (!nextframe || nextframe <= tvref(L->maxstack)));
    fn = frame_func(frame);
    lua_assert(fn->c.gct == ~LJ_TFUNC);
  }
  for (; *what; what++) {
    if (*what == 'S') {
      if (isluafunc(fn)) {
	GCproto *pt = funcproto(fn);
	BCLine firstline = pt->firstline;
	GCstr *name = proto_chunkname(pt);
	ar->source = strdata(name);
	lj_debug_shortname(ar->short_src, name, pt->firstline);
	ar->linedefined = (int)firstline;
	ar->lastlinedefined = (int)(firstline + pt->numline);
	ar->what = (firstline || !pt->numline) ? "Lua" : "main";
      } else {
	ar->source = "=[C]";
	ar->short_src[0] = '[';
	ar->short_src[1] = 'C';
	ar->short_src[2] = ']';
	ar->short_src[3] = '\0';
	ar->linedefined = -1;
	ar->lastlinedefined = -1;
	ar->what = "C";
      }
    } else if (*what == 'l') {
      ar->currentline = frame ? debug_frameline(L, fn, nextframe) : -1;
    } else if (*what == 'u') {
      ar->nups = fn->c.nupvalues;
      if (ext) {
	if (isluafunc(fn)) {
	  GCproto *pt = funcproto(fn);
	  ar->nparams = pt->numparams;
	  ar->isvararg = !!(pt->flags & PROTO_VARARG);
	} else {
	  ar->nparams = 0;
	  ar->isvararg = 1;
	}
      }
    } else if (*what == 'n') {
      ar->namewhat = frame ? lj_debug_funcname(L, frame, &ar->name) : NULL;
      if (ar->namewhat == NULL) {
	ar->namewhat = "";
	ar->name = NULL;
      }
    } else if (*what == 'f') {
      opt_f = 1;
    } else if (*what == 'L') {
      opt_L = 1;
    } else {
      return 0;  /* Bad option. */
    }
  }
  if (opt_f) {
    setfuncV(L, L->top, fn);
    incr_top(L);
  }
  if (opt_L) {
    if (isluafunc(fn)) {
      GCtab *t = lj_tab_new(L, 0, 0);
      GCproto *pt = funcproto(fn);
      const void *lineinfo = proto_lineinfo(pt);
      if (lineinfo) {
	BCLine first = pt->firstline;
	int sz = pt->numline < 256 ? 1 : pt->numline < 65536 ? 2 : 4;
	MSize i, szl = pt->sizebc-1;
	for (i = 0; i < szl; i++) {
	  BCLine line = first +
	    (sz == 1 ? (BCLine)((const uint8_t *)lineinfo)[i] :
	     sz == 2 ? (BCLine)((const uint16_t *)lineinfo)[i] :
	     (BCLine)((const uint32_t *)lineinfo)[i]);
	  setboolV(lj_tab_setint(L, t, line), 1);
	}
      }
      settabV(L, L->top, t);
    } else {
      setnilV(L->top);
    }
    incr_top(L);
  }
  return 1;  /* Ok. */
}