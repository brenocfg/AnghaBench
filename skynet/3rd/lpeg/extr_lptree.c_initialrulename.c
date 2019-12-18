#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int key; } ;
typedef  int /*<<< orphan*/  TTree ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int lua_rawlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* sib1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void initialrulename (lua_State *L, TTree *grammar, int frule) {
  if (sib1(grammar)->key == 0) {  /* initial rule is not referenced? */
    int n = lua_rawlen(L, -1) + 1;  /* index for name */
    lua_pushvalue(L, frule);  /* rule's name */
    lua_rawseti(L, -2, n);  /* ktable was on the top of the stack */
    sib1(grammar)->key = n;
  }
}