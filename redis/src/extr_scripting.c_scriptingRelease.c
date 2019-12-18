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
struct TYPE_2__ {int /*<<< orphan*/  lua; scalar_t__ lua_scripts_mem; int /*<<< orphan*/  lua_scripts; } ;

/* Variables and functions */
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 

void scriptingRelease(void) {
    dictRelease(server.lua_scripts);
    server.lua_scripts_mem = 0;
    lua_close(server.lua);
}