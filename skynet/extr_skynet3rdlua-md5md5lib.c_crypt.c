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
 size_t BLOCKSIZE ; 
 int /*<<< orphan*/  MAXKEY ; 
 int /*<<< orphan*/  checkseed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  codestream (int /*<<< orphan*/ *,char const*,size_t,char*,int) ; 
 int initblock (int /*<<< orphan*/ *,char const*,size_t,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  lua_concat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int crypt (lua_State *L) {
  size_t lmsg;
  const char *msg = luaL_checklstring(L, 1, &lmsg);
  size_t lseed;
  const char *seed;
  int lblock;
  char block[BLOCKSIZE+MAXKEY];
  checkseed(L);
  seed = luaL_checklstring(L, 3, &lseed);
  if (lseed > BLOCKSIZE)
    luaL_error(L, "seed too long (> %d)", BLOCKSIZE);
  /* put seed and seed length at the beginning of result */
  block[0] = (char)lseed;
  memcpy(block+1, seed, lseed);
  lua_pushlstring(L, block, lseed+1);  /* to concat with result */
  lblock = initblock(L, seed, lseed, block);
  codestream(L, msg, lmsg, block, lblock);
  lua_concat(L, 2);
  return 1;
}