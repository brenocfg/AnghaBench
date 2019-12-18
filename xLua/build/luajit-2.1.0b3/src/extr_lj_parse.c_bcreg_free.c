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
struct TYPE_3__ {scalar_t__ nactvar; scalar_t__ freereg; } ;
typedef  TYPE_1__ FuncState ;
typedef  scalar_t__ BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void bcreg_free(FuncState *fs, BCReg reg)
{
  if (reg >= fs->nactvar) {
    fs->freereg--;
    lua_assert(reg == fs->freereg);
  }
}