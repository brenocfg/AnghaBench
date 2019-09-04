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
struct table {int /*<<< orphan*/ * hash; int /*<<< orphan*/  L; scalar_t__ sizehash; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  pushkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pushfirsthash(lua_State *L, struct table * tbl) {
	if (tbl->sizehash) {
		pushkey(L, tbl->L, &tbl->hash[0]);
		return 1;
	} else {
		return 0;
	}
}