#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int checkupval (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueid (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int db_upvalueid (lua_State *L) {
  int n = checkupval(L, 1, 2);
  lua_pushlightuserdata(L, lua_upvalueid(L, 1, n));
  return 1;
}