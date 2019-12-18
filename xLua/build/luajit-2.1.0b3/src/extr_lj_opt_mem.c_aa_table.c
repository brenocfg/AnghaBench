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
struct TYPE_5__ {scalar_t__ o; int /*<<< orphan*/  t; } ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  AliasRet ;

/* Variables and functions */
 int /*<<< orphan*/  ALIAS_MAY ; 
 int /*<<< orphan*/  ALIAS_NO ; 
 TYPE_1__* IR (scalar_t__) ; 
 scalar_t__ IR_TDUP ; 
 scalar_t__ IR_TNEW ; 
 int /*<<< orphan*/  aa_escape (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ irt_istab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static AliasRet aa_table(jit_State *J, IRRef ta, IRRef tb)
{
  IRIns *taba = IR(ta), *tabb = IR(tb);
  int newa, newb;
  lua_assert(ta != tb);
  lua_assert(irt_istab(taba->t) && irt_istab(tabb->t));
  /* Disambiguate new allocations. */
  newa = (taba->o == IR_TNEW || taba->o == IR_TDUP);
  newb = (tabb->o == IR_TNEW || tabb->o == IR_TDUP);
  if (newa && newb)
    return ALIAS_NO;  /* Two different allocations never alias. */
  if (newb) {  /* At least one allocation? */
    IRIns *tmp = taba; taba = tabb; tabb = tmp;
  } else if (!newa) {
    return ALIAS_MAY;  /* Anything else: we just don't know. */
  }
  return aa_escape(J, taba, tabb);
}