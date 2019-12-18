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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ ** tofilep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_tostring (lua_State *L) {
  FILE *f = *tofilep(L);
  if (f == NULL)
    lua_pushliteral(L, "file (closed)");
  else
    lua_pushfstring(L, "file (%p)", f);
  return 1;
}