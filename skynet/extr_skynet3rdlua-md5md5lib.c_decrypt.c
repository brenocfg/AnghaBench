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
 int /*<<< orphan*/  decodestream (int /*<<< orphan*/ *,char const*,size_t,char*,int) ; 
 int initblock (int /*<<< orphan*/ *,char const*,size_t,char*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 

__attribute__((used)) static int decrypt (lua_State *L) {
  size_t lcyphertext;
  const char *cyphertext = luaL_checklstring(L, 1, &lcyphertext);
  size_t lseed = cyphertext[0];
  const char *seed = cyphertext+1;
  int lblock;
  char block[BLOCKSIZE+MAXKEY];
  luaL_argcheck(L, lcyphertext >= lseed+1 && lseed <= BLOCKSIZE, 1,
                 "invalid cyphered string");
  cyphertext += lseed+1;
  lcyphertext -= lseed+1;
  lblock = initblock(L, seed, lseed, block);
  decodestream(L, cyphertext, lcyphertext, block, lblock);
  return 1;
}