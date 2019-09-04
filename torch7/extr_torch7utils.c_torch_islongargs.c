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
 scalar_t__ luaT_toudata (int /*<<< orphan*/ *,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 

int torch_islongargs(lua_State *L, int index)
{
  int narg = lua_gettop(L)-index+1;

  if(narg == 1 && luaT_toudata(L, index, "torch.LongStorage"))
  {
    return 1;
  }
  else
  {
    int i;

    for(i = index; i < index+narg; i++)
    {
      if(!lua_isnumber(L, i))
        return 0;
    }
    return 1;
  }
  return 0;
}