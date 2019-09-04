#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ Pattern ;
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 int /*<<< orphan*/ * compile (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  finalfix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getuservalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Instruction *prepcompile (lua_State *L, Pattern *p, int idx) {
  lua_getuservalue(L, idx);  /* push 'ktable' (may be used by 'finalfix') */
  finalfix(L, 0, NULL, p->tree);
  lua_pop(L, 1);  /* remove 'ktable' */
  return compile(L, p);
}