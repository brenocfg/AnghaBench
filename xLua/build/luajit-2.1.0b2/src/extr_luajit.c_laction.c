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

/* Variables and functions */
 int LUA_MASKCALL ; 
 int LUA_MASKCOUNT ; 
 int LUA_MASKRET ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  globalL ; 
 int /*<<< orphan*/  lstop ; 
 int /*<<< orphan*/  lua_sethook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void laction(int i)
{
  signal(i, SIG_DFL); /* if another SIGINT happens before lstop,
			 terminate process (default action) */
  lua_sethook(globalL, lstop, LUA_MASKCALL | LUA_MASKRET | LUA_MASKCOUNT, 1);
}