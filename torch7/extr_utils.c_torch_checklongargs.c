#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {int size; } ;
typedef  TYPE_1__ THLongStorage ;

/* Variables and functions */
 int /*<<< orphan*/  THLongStorage_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  THLongStorage_free (TYPE_1__*) ; 
 TYPE_1__* THLongStorage_newWithSize (int) ; 
 int /*<<< orphan*/  THLongStorage_set (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 TYPE_1__* luaT_toudata (int /*<<< orphan*/ *,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 

THLongStorage* torch_checklongargs(lua_State *L, int index)
{
  THLongStorage *storage;
  int i;
  int narg = lua_gettop(L)-index+1;

  if(narg == 1 && luaT_toudata(L, index, "torch.LongStorage"))
  {
    THLongStorage *storagesrc = luaT_toudata(L, index, "torch.LongStorage");
    storage = THLongStorage_newWithSize(storagesrc->size);
    THLongStorage_copy(storage, storagesrc);
  }
  else
  {
    storage = THLongStorage_newWithSize(narg);
    for(i = index; i < index+narg; i++)
    {
      if(!lua_isnumber(L, i))
      {
        THLongStorage_free(storage);
        luaL_argerror(L, i, "number expected");
      }
      THLongStorage_set(storage, i-index, lua_tonumber(L, i));
    }
  }
  return storage;
}