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
typedef  int /*<<< orphan*/  THGenerator ;

/* Variables and functions */
 int /*<<< orphan*/  THGenerator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaT_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  torch_Generator ; 

int torch_Generator_free(lua_State *L)
{
  THGenerator *gen= luaT_checkudata(L, 1, torch_Generator);
  THGenerator_free(gen);
  return 0;
}