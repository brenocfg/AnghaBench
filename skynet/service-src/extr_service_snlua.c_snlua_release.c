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
struct snlua {int /*<<< orphan*/  L; } ;

/* Variables and functions */
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_free (struct snlua*) ; 

void
snlua_release(struct snlua *l) {
	lua_close(l->L);
	skynet_free(l);
}