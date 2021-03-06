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
struct TYPE_3__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ thread ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  aeStop (int /*<<< orphan*/ ) ; 
 TYPE_1__* checkthread (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int script_thread_stop(lua_State *L) {
    thread *t = checkthread(L);
    aeStop(t->loop);
    return 0;
}