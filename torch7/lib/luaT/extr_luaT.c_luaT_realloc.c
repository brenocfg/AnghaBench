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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 void* luaT_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaT_free (int /*<<< orphan*/ *,void*) ; 
 void* realloc (void*,int) ; 

void* luaT_realloc(lua_State *L, void *ptr, ptrdiff_t size)
{
  if(!ptr)
    return(luaT_alloc(L, size));

  if(size == 0)
  {
    luaT_free(L, ptr);
    return NULL;
  }

  if(size < 0)
    luaL_error(L, "$ Torch: invalid memory size -- maybe an overflow?");

  ptr = realloc(ptr, size);
  if(!ptr)
    luaL_error(L, "$ Torch: not enough memory: you tried to reallocate %dGB. Buy new RAM!", size/1073741824);
  return ptr;
}