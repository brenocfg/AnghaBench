#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  mmudata; } ;
struct TYPE_4__ {TYPE_1__ gc; } ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gcref (int /*<<< orphan*/ ) ; 

void lj_gc_finalize_udata(lua_State *L)
{
  while (gcref(G(L)->gc.mmudata) != NULL)
    gc_finalize(L);
}