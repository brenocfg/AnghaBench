#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {scalar_t__ tag; int /*<<< orphan*/  key; } ;
struct TYPE_7__ {int ps; } ;
struct TYPE_8__ {int /*<<< orphan*/  key; TYPE_1__ u; int /*<<< orphan*/  tag; } ;
typedef  TYPE_2__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  TCall ; 
 scalar_t__ TRule ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* sib2 (TYPE_2__*) ; 
 int /*<<< orphan*/  val2str (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fixonecall (lua_State *L, int postable, TTree *g, TTree *t) {
  int n;
  lua_rawgeti(L, -1, t->key);  /* get rule's name */
  lua_gettable(L, postable);  /* query name in position table */
  n = lua_tonumber(L, -1);  /* get (absolute) position */
  lua_pop(L, 1);  /* remove position */
  if (n == 0) {  /* no position? */
    lua_rawgeti(L, -1, t->key);  /* get rule's name again */
    luaL_error(L, "rule '%s' undefined in given grammar", val2str(L, -1));
  }
  t->tag = TCall;
  t->u.ps = n - (t - g);  /* position relative to node */
  assert(sib2(t)->tag == TRule);
  sib2(t)->key = t->key;  /* fix rule's key */
}