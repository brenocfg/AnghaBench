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
typedef  int /*<<< orphan*/  THFile ;

/* Variables and functions */
 int /*<<< orphan*/  THFile_readByteRaw (int /*<<< orphan*/ *,unsigned char*,int) ; 
 void* luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 char* torch_Generator ; 

__attribute__((used)) static int torch_Generator_read(lua_State *L)
{
  THGenerator *gen = luaT_checkudata(L, 1, torch_Generator);
  THFile *file = luaT_checkudata(L, 2, "torch.File");

  THFile_readByteRaw(file, (unsigned char *)gen, sizeof(THGenerator));
  return 0;
}