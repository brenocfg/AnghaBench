#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int top; TYPE_2__* ci; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_9__ {int func; int base; } ;
typedef  int StkId ;
typedef  int /*<<< orphan*/  Proto ;
typedef  TYPE_2__ CallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  currentpc (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * getluaproto (TYPE_2__*) ; 
 char* luaF_getlocalname (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *findlocal (lua_State *L, CallInfo *ci, int n) {
  const char *name;
  Proto *fp = getluaproto(ci);
  if (fp && (name = luaF_getlocalname(fp, n, currentpc(L, ci))) != NULL)
    return name;  /* is a local variable in a Lua function */
  else {
    StkId limit = (ci == L->ci) ? L->top : (ci+1)->func;
    if (limit - ci->base >= n && n > 0)  /* is 'n' inside 'ci' stack? */
      return "(*temporary)";
    else
      return NULL;
  }
}