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
struct snlua {int /*<<< orphan*/  L; scalar_t__ mem_limit; int /*<<< orphan*/  mem_report; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMORY_WARNING_REPORT ; 
 int /*<<< orphan*/  lalloc ; 
 int /*<<< orphan*/  lua_newstate (int /*<<< orphan*/ ,struct snlua*) ; 
 int /*<<< orphan*/  memset (struct snlua*,int /*<<< orphan*/ ,int) ; 
 struct snlua* skynet_malloc (int) ; 

struct snlua *
snlua_create(void) {
	struct snlua * l = skynet_malloc(sizeof(*l));
	memset(l,0,sizeof(*l));
	l->mem_report = MEMORY_WARNING_REPORT;
	l->mem_limit = 0;
	l->L = lua_newstate(lalloc, l);
	return l;
}