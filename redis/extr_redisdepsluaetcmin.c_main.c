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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ luaL_dofile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_open () ; 
 int /*<<< orphan*/  lua_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
 lua_State *L=lua_open();
 lua_register(L,"print",print);
 if (luaL_dofile(L,NULL)!=0) fprintf(stderr,"%s\n",lua_tostring(L,-1));
 lua_close(L);
 return 0;
}