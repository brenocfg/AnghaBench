#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  scalar_t__ int32_t ;
struct TYPE_13__ {int /*<<< orphan*/  n; } ;
struct TYPE_11__ {int /*<<< orphan*/  n; } ;
struct TYPE_12__ {TYPE_1__ val; TYPE_3__ key; } ;
typedef  TYPE_1__ TValue ;
typedef  TYPE_2__ Node ;
typedef  int /*<<< orphan*/  GCtab ;

/* Variables and functions */
 TYPE_2__* hashnum (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* lj_tab_newkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* nextnode (TYPE_2__*) ; 
 scalar_t__ tvisnum (TYPE_3__*) ; 

TValue *lj_tab_setinth(lua_State *L, GCtab *t, int32_t key)
{
  TValue k;
  Node *n;
  k.n = (lua_Number)key;
  n = hashnum(t, &k);
  do {
    if (tvisnum(&n->key) && n->key.n == k.n)
      return &n->val;
  } while ((n = nextnode(n)));
  return lj_tab_newkey(L, t, &k);
}