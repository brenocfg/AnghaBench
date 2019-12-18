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
typedef  int /*<<< orphan*/  Proto ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IS (char*) ; 
 scalar_t__ LUA_OK ; 
 int /*<<< orphan*/  cannot (char*) ; 
 int /*<<< orphan*/ * combine (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dumping ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int listing ; 
 scalar_t__ luaL_loadfile (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaU_dump (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaU_print (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  lua_checkstack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * output ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  stripping ; 
 int /*<<< orphan*/  writer ; 

__attribute__((used)) static int pmain(lua_State* L)
{
 int argc=(int)lua_tointeger(L,1);
 char** argv=(char**)lua_touserdata(L,2);
 const Proto* f;
 int i;
 if (!lua_checkstack(L,argc)) fatal("too many input files");
 for (i=0; i<argc; i++)
 {
  const char* filename=IS("-") ? NULL : argv[i];
  if (luaL_loadfile(L,filename)!=LUA_OK) fatal(lua_tostring(L,-1));
 }
 f=combine(L,argc);
 if (listing) luaU_print(f,listing>1);
 if (dumping)
 {
  FILE* D= (output==NULL) ? stdout : fopen(output,"wb");
  if (D==NULL) cannot("open");
  lua_lock(L);
  luaU_dump(L,f,writer,D,stripping);
  lua_unlock(L);
  if (ferror(D)) cannot("write");
  if (fclose(D)) cannot("close");
 }
 return 0;
}