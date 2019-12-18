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
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  savetv ;
struct TYPE_13__ {void** base; size_t maxslot; TYPE_3__* L; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_15__ {int /*<<< orphan*/ * base; } ;
struct TYPE_14__ {void* key; void* tab; int /*<<< orphan*/  tabv; int /*<<< orphan*/  keyv; } ;
struct TYPE_12__ {int /*<<< orphan*/  strempty; int /*<<< orphan*/  tmpbuf; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  void* TRef ;
typedef  TYPE_2__ RecordIndex ;
typedef  size_t BCReg ;

/* Variables and functions */
 void* IRBUFHDR_RESET ; 
 int /*<<< orphan*/  IRT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* IRTOSTR_INT ; 
 void* IRTOSTR_NUM ; 
 int /*<<< orphan*/  IRT_PGC ; 
 int /*<<< orphan*/  IRT_STR ; 
 int /*<<< orphan*/  IR_BUFHDR ; 
 int /*<<< orphan*/  IR_BUFPUT ; 
 int /*<<< orphan*/  IR_BUFSTR ; 
 int /*<<< orphan*/  IR_TOSTR ; 
 TYPE_10__* J2G (TYPE_1__*) ; 
 int /*<<< orphan*/  MM_concat ; 
 int /*<<< orphan*/  copyTV (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* emitir (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  getslot (TYPE_1__*,size_t) ; 
 void* lj_ir_kptr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rec_mm_arith (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setstrV (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tref_isnum (void*) ; 
 scalar_t__ tref_isnumber (void*) ; 
 scalar_t__ tref_isnumber_str (void*) ; 
 int /*<<< orphan*/  tref_isstr (void*) ; 

__attribute__((used)) static TRef rec_cat(jit_State *J, BCReg baseslot, BCReg topslot)
{
  TRef *top = &J->base[topslot];
  TValue savetv[5];
  BCReg s;
  RecordIndex ix;
  lua_assert(baseslot < topslot);
  for (s = baseslot; s <= topslot; s++)
    (void)getslot(J, s);  /* Ensure all arguments have a reference. */
  if (tref_isnumber_str(top[0]) && tref_isnumber_str(top[-1])) {
    TRef tr, hdr, *trp, *xbase, *base = &J->base[baseslot];
    /* First convert numbers to strings. */
    for (trp = top; trp >= base; trp--) {
      if (tref_isnumber(*trp))
	*trp = emitir(IRT(IR_TOSTR, IRT_STR), *trp,
		      tref_isnum(*trp) ? IRTOSTR_NUM : IRTOSTR_INT);
      else if (!tref_isstr(*trp))
	break;
    }
    xbase = ++trp;
    tr = hdr = emitir(IRT(IR_BUFHDR, IRT_PGC),
		      lj_ir_kptr(J, &J2G(J)->tmpbuf), IRBUFHDR_RESET);
    do {
      tr = emitir(IRT(IR_BUFPUT, IRT_PGC), tr, *trp++);
    } while (trp <= top);
    tr = emitir(IRT(IR_BUFSTR, IRT_STR), tr, hdr);
    J->maxslot = (BCReg)(xbase - J->base);
    if (xbase == base) return tr;  /* Return simple concatenation result. */
    /* Pass partial result. */
    topslot = J->maxslot--;
    *xbase = tr;
    top = xbase;
    setstrV(J->L, &ix.keyv, &J2G(J)->strempty);  /* Simulate string result. */
  } else {
    J->maxslot = topslot-1;
    copyTV(J->L, &ix.keyv, &J->L->base[topslot]);
  }
  copyTV(J->L, &ix.tabv, &J->L->base[topslot-1]);
  ix.tab = top[-1];
  ix.key = top[0];
  memcpy(savetv, &J->L->base[topslot-1], sizeof(savetv));  /* Save slots. */
  rec_mm_arith(J, &ix, MM_concat);  /* Call __concat metamethod. */
  memcpy(&J->L->base[topslot-1], savetv, sizeof(savetv));  /* Restore slots. */
  return 0;  /* No result yet. */
}