#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_4__* ci; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_14__ {int base; } ;
struct TYPE_15__ {TYPE_1__ l; } ;
struct TYPE_17__ {TYPE_2__ u; } ;
struct TYPE_13__ {int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_4__ CallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  cast_int (int /*<<< orphan*/  const*) ; 
 TYPE_11__* ci_func (TYPE_4__*) ; 
 int /*<<< orphan*/  currentpc (TYPE_4__*) ; 
 char* getobjname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 char* getupvalname (TYPE_4__*,int /*<<< orphan*/  const*,char const**) ; 
 scalar_t__ isLua (TYPE_4__*) ; 
 scalar_t__ isinstack (TYPE_4__*,int /*<<< orphan*/  const*) ; 
 char const* luaO_pushfstring (TYPE_3__*,char*,char const*,char const*) ; 

__attribute__((used)) static const char *varinfo (lua_State *L, const TValue *o) {
  const char *name = NULL;  /* to avoid warnings */
  CallInfo *ci = L->ci;
  const char *kind = NULL;
  if (isLua(ci)) {
    kind = getupvalname(ci, o, &name);  /* check whether 'o' is an upvalue */
    if (!kind && isinstack(ci, o))  /* no? try a register */
      kind = getobjname(ci_func(ci)->p, currentpc(ci),
                        cast_int(o - ci->u.l.base), &name);
  }
  return (kind) ? luaO_pushfstring(L, " (%s '%s')", kind, name) : "";
}