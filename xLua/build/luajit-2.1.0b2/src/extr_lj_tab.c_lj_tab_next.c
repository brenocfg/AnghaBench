#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_8__ {size_t asize; size_t hmask; int /*<<< orphan*/  node; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ Node ;
typedef  TYPE_2__ GCtab ;

/* Variables and functions */
 int /*<<< orphan*/ * arrayslot (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  copyTV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t keyindex (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* noderef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 

int lj_tab_next(lua_State *L, GCtab *t, TValue *key)
{
  uint32_t i = keyindex(L, t, key);  /* Find predecessor key index. */
  for (i++; i < t->asize; i++)  /* First traverse the array keys. */
    if (!tvisnil(arrayslot(t, i))) {
      setintV(key, i);
      copyTV(L, key+1, arrayslot(t, i));
      return 1;
    }
  for (i -= t->asize; i <= t->hmask; i++) {  /* Then traverse the hash keys. */
    Node *n = &noderef(t->node)[i];
    if (!tvisnil(&n->val)) {
      copyTV(L, key, &n->key);
      copyTV(L, key+1, &n->val);
      return 1;
    }
  }
  return 0;  /* End of traversal. */
}