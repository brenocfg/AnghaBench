#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  ZIO ;
struct TYPE_4__ {char const* name; int /*<<< orphan*/ * b; int /*<<< orphan*/ * Z; int /*<<< orphan*/ * L; } ;
typedef  int /*<<< orphan*/  Proto ;
typedef  int /*<<< orphan*/  Mbuffer ;
typedef  TYPE_1__ LoadState ;

/* Variables and functions */
 char const* LUA_SIGNATURE ; 
 int /*<<< orphan*/ * LoadFunction (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadHeader (TYPE_1__*) ; 
 int /*<<< orphan*/  luaS_newliteral (int /*<<< orphan*/ *,char*) ; 

Proto* luaU_undump (lua_State* L, ZIO* Z, Mbuffer* buff, const char* name)
{
 LoadState S;
 if (*name=='@' || *name=='=')
  S.name=name+1;
 else if (*name==LUA_SIGNATURE[0])
  S.name="binary string";
 else
  S.name=name;
 S.L=L;
 S.Z=Z;
 S.b=buff;
 LoadHeader(&S);
 return LoadFunction(&S,luaS_newliteral(L,"=?"));
}