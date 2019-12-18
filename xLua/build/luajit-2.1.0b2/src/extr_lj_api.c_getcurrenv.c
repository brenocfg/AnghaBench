#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  env; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  env; int /*<<< orphan*/  gct; } ;
struct TYPE_9__ {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  TYPE_3__ GCfunc ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_TFUNC ; 
 TYPE_3__* curr_func (TYPE_2__*) ; 
 int /*<<< orphan*/ * tabref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GCtab *getcurrenv(lua_State *L)
{
  GCfunc *fn = curr_func(L);
  return fn->c.gct == ~LJ_TFUNC ? tabref(fn->c.env) : tabref(L->env);
}