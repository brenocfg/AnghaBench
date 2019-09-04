#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  l_noret ;
struct TYPE_9__ {int /*<<< orphan*/ * L; } ;
struct TYPE_8__ {TYPE_4__* ls; TYPE_2__* f; } ;
struct TYPE_7__ {TYPE_1__* sp; } ;
struct TYPE_6__ {int linedefined; } ;
typedef  TYPE_3__ FuncState ;

/* Variables and functions */
 char* luaO_pushfstring (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  luaX_syntaxerror (TYPE_4__*,char const*) ; 

__attribute__((used)) static l_noret errorlimit (FuncState *fs, int limit, const char *what) {
  lua_State *L = fs->ls->L;
  const char *msg;
  int line = fs->f->sp->linedefined;
  const char *where = (line == 0)
                      ? "main function"
                      : luaO_pushfstring(L, "function at line %d", line);
  msg = luaO_pushfstring(L, "too many %s (limit is %d) in %s",
                             what, limit, where);
  luaX_syntaxerror(fs->ls, msg);
}