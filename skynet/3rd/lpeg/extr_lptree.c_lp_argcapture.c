#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int key; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  Carg ; 
 int SHRT_MAX ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* newemptycap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp_argcapture (lua_State *L) {
  int n = (int)luaL_checkinteger(L, 1);
  TTree *tree = newemptycap(L, Carg);
  tree->key = n;
  luaL_argcheck(L, 0 < n && n <= SHRT_MAX, 1, "invalid argument index");
  return 1;
}