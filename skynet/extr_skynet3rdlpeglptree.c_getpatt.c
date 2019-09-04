#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_12__ {int /*<<< orphan*/  tag; } ;
struct TYPE_11__ {int /*<<< orphan*/  key; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
#define  LUA_TBOOLEAN 132 
#define  LUA_TFUNCTION 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  TChar ; 
 int /*<<< orphan*/  TFalse ; 
 int /*<<< orphan*/  TRunTime ; 
 int /*<<< orphan*/  TTrue ; 
 int /*<<< orphan*/  addtonewktable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fillseq (TYPE_1__*,int /*<<< orphan*/ ,size_t,char const*) ; 
 int getsize (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* gettree (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* newgrammar (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* newleaf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* newtree (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* numtree (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* sib1 (TYPE_1__*) ; 

__attribute__((used)) static TTree *getpatt (lua_State *L, int idx, int *len) {
  TTree *tree;
  switch (lua_type(L, idx)) {
    case LUA_TSTRING: {
      size_t slen;
      const char *s = lua_tolstring(L, idx, &slen);  /* get string */
      if (slen == 0)  /* empty? */
        tree = newleaf(L, TTrue);  /* always match */
      else {
        tree = newtree(L, 2 * (slen - 1) + 1);
        fillseq(tree, TChar, slen, s);  /* sequence of 'slen' chars */
      }
      break;
    }
    case LUA_TNUMBER: {
      int n = lua_tointeger(L, idx);
      tree = numtree(L, n);
      break;
    }
    case LUA_TBOOLEAN: {
      tree = (lua_toboolean(L, idx) ? newleaf(L, TTrue) : newleaf(L, TFalse));
      break;
    }
    case LUA_TTABLE: {
      tree = newgrammar(L, idx);
      break;
    }
    case LUA_TFUNCTION: {
      tree = newtree(L, 2);
      tree->tag = TRunTime;
      tree->key = addtonewktable(L, 0, idx);
      sib1(tree)->tag = TTrue;
      break;
    }
    default: {
      return gettree(L, idx, len);
    }
  }
  lua_replace(L, idx);  /* put new tree into 'idx' slot */
  if (len)
    *len = getsize(L, idx);
  return tree;
}