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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  extra; } ;
typedef  TYPE_1__ TString ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_ENV ; 
 int NUM_RESERVED ; 
 int /*<<< orphan*/  cast_byte (int) ; 
 int /*<<< orphan*/  luaC_fix (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* luaS_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* luaS_newliteral (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * luaX_tokens ; 
 int /*<<< orphan*/  obj2gco (TYPE_1__*) ; 

void luaX_init (lua_State *L) {
  int i;
  TString *e = luaS_newliteral(L, LUA_ENV);  /* create env name */
  luaC_fix(L, obj2gco(e));  /* never collect this name */
  for (i=0; i<NUM_RESERVED; i++) {
    TString *ts = luaS_new(L, luaX_tokens[i]);
    luaC_fix(L, obj2gco(ts));  /* reserved words are never collected */
    ts->extra = cast_byte(i+1);  /* reserved word */
  }
}