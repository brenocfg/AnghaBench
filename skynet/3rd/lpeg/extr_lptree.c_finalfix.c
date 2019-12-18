#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {int tag; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
#define  TChoice 131 
#define  TGrammar 130 
#define  TOpenCall 129 
#define  TSeq 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  correctassociativity (TYPE_1__*) ; 
 int /*<<< orphan*/  fixonecall (int /*<<< orphan*/ *,int,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int* numsiblings ; 
 TYPE_1__* sib1 (TYPE_1__*) ; 
 TYPE_1__* sib2 (TYPE_1__*) ; 
 int /*<<< orphan*/  val2str (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void finalfix (lua_State *L, int postable, TTree *g, TTree *t) {
 tailcall:
  switch (t->tag) {
    case TGrammar:  /* subgrammars were already fixed */
      return;
    case TOpenCall: {
      if (g != NULL)  /* inside a grammar? */
        fixonecall(L, postable, g, t);
      else {  /* open call outside grammar */
        lua_rawgeti(L, -1, t->key);
        luaL_error(L, "rule '%s' used outside a grammar", val2str(L, -1));
      }
      break;
    }
    case TSeq: case TChoice:
      correctassociativity(t);
      break;
  }
  switch (numsiblings[t->tag]) {
    case 1: /* finalfix(L, postable, g, sib1(t)); */
      t = sib1(t); goto tailcall;
    case 2:
      finalfix(L, postable, g, sib1(t));
      t = sib2(t); goto tailcall;  /* finalfix(L, postable, g, sib2(t)); */
    default: assert(numsiblings[t->tag] == 0); break;
  }
}