#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ LStream ;

/* Variables and functions */
 int fclose (int /*<<< orphan*/ ) ; 
 int luaL_fileresult (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* tolstream (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_fclose (lua_State *L) {
  LStream *p = tolstream(L);
  int res = fclose(p->f);
  return luaL_fileresult(L, (res == 0), NULL);
}