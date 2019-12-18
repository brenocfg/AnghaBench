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
struct channel_box {int /*<<< orphan*/ * c; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/ * channel_release (int /*<<< orphan*/ *) ; 
 struct channel_box* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lrelease(lua_State *L) {
	struct channel_box *cb = lua_touserdata(L, 1);
	if (cb) {
		if (channel_release(cb->c) == NULL) {
			cb->c = NULL;
		}
	}

	return 0;
}