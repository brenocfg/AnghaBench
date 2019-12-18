#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {scalar_t__ op2; scalar_t__ o; scalar_t__ op1; scalar_t__ i; int /*<<< orphan*/  t; } ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  AliasRet ;

/* Variables and functions */
 int /*<<< orphan*/  ALIAS_MAY ; 
 int /*<<< orphan*/  ALIAS_MUST ; 
 int /*<<< orphan*/  ALIAS_NO ; 
 TYPE_1__* IR (scalar_t__) ; 
 scalar_t__ IR_ADD ; 
 scalar_t__ IR_AREF ; 
 scalar_t__ IR_HREF ; 
 scalar_t__ IR_HREFK ; 
 scalar_t__ IR_KSLOT ; 
 scalar_t__ IR_NEWREF ; 
 int /*<<< orphan*/  aa_table (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ irref_isk (scalar_t__) ; 
 int /*<<< orphan*/  irt_sametype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static AliasRet aa_ahref(jit_State *J, IRIns *refa, IRIns *refb)
{
  IRRef ka = refa->op2;
  IRRef kb = refb->op2;
  IRIns *keya, *keyb;
  IRRef ta, tb;
  if (refa == refb)
    return ALIAS_MUST;  /* Shortcut for same refs. */
  keya = IR(ka);
  if (keya->o == IR_KSLOT) { ka = keya->op1; keya = IR(ka); }
  keyb = IR(kb);
  if (keyb->o == IR_KSLOT) { kb = keyb->op1; keyb = IR(kb); }
  ta = (refa->o==IR_HREFK || refa->o==IR_AREF) ? IR(refa->op1)->op1 : refa->op1;
  tb = (refb->o==IR_HREFK || refb->o==IR_AREF) ? IR(refb->op1)->op1 : refb->op1;
  if (ka == kb) {
    /* Same key. Check for same table with different ref (NEWREF vs. HREF). */
    if (ta == tb)
      return ALIAS_MUST;  /* Same key, same table. */
    else
      return aa_table(J, ta, tb);  /* Same key, possibly different table. */
  }
  if (irref_isk(ka) && irref_isk(kb))
    return ALIAS_NO;  /* Different constant keys. */
  if (refa->o == IR_AREF) {
    /* Disambiguate array references based on index arithmetic. */
    int32_t ofsa = 0, ofsb = 0;
    IRRef basea = ka, baseb = kb;
    lua_assert(refb->o == IR_AREF);
    /* Gather base and offset from t[base] or t[base+-ofs]. */
    if (keya->o == IR_ADD && irref_isk(keya->op2)) {
      basea = keya->op1;
      ofsa = IR(keya->op2)->i;
      if (basea == kb && ofsa != 0)
	return ALIAS_NO;  /* t[base+-ofs] vs. t[base]. */
    }
    if (keyb->o == IR_ADD && irref_isk(keyb->op2)) {
      baseb = keyb->op1;
      ofsb = IR(keyb->op2)->i;
      if (ka == baseb && ofsb != 0)
	return ALIAS_NO;  /* t[base] vs. t[base+-ofs]. */
    }
    if (basea == baseb && ofsa != ofsb)
      return ALIAS_NO;  /* t[base+-o1] vs. t[base+-o2] and o1 != o2. */
  } else {
    /* Disambiguate hash references based on the type of their keys. */
    lua_assert((refa->o==IR_HREF || refa->o==IR_HREFK || refa->o==IR_NEWREF) &&
	       (refb->o==IR_HREF || refb->o==IR_HREFK || refb->o==IR_NEWREF));
    if (!irt_sametype(keya->t, keyb->t))
      return ALIAS_NO;  /* Different key types. */
  }
  if (ta == tb)
    return ALIAS_MAY;  /* Same table, cannot disambiguate keys. */
  else
    return aa_table(J, ta, tb);  /* Try to disambiguate tables. */
}