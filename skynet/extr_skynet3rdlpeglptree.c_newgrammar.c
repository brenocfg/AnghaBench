#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {int n; } ;
struct TYPE_11__ {TYPE_1__ u; int /*<<< orphan*/  tag; } ;
typedef  TYPE_2__ TTree ;

/* Variables and functions */
 int MAXRULES ; 
 int /*<<< orphan*/  TGrammar ; 
 int /*<<< orphan*/  buildgrammar (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 int collectrules (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  finalfix (int /*<<< orphan*/ *,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialrulename (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getuservalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setuservalue (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* newtree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sib1 (TYPE_2__*) ; 
 int /*<<< orphan*/  verifygrammar (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static TTree *newgrammar (lua_State *L, int arg) {
  int treesize;
  int frule = lua_gettop(L) + 2;  /* position of first rule's key */
  int n = collectrules(L, arg, &treesize);
  TTree *g = newtree(L, treesize);
  luaL_argcheck(L, n <= MAXRULES, arg, "grammar has too many rules");
  g->tag = TGrammar;  g->u.n = n;
  lua_newtable(L);  /* create 'ktable' */
  lua_setuservalue(L, -2);
  buildgrammar(L, g, frule, n);
  lua_getuservalue(L, -1);  /* get 'ktable' for new tree */
  finalfix(L, frule - 1, g, sib1(g));
  initialrulename(L, g, frule);
  verifygrammar(L, g);
  lua_pop(L, 1);  /* remove 'ktable' */
  lua_insert(L, -(n * 2 + 2));  /* move new table to proper position */
  lua_pop(L, n * 2 + 1);  /* remove position table + rule pairs */
  return g;  /* new table at the top of the stack */
}