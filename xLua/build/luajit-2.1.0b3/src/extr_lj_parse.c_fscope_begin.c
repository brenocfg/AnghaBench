#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {int flags; struct TYPE_8__* prev; int /*<<< orphan*/  vstart; scalar_t__ nactvar; } ;
struct TYPE_7__ {scalar_t__ nactvar; scalar_t__ freereg; TYPE_3__* bl; TYPE_1__* ls; } ;
struct TYPE_6__ {int /*<<< orphan*/  vtop; } ;
typedef  TYPE_2__ FuncState ;
typedef  TYPE_3__ FuncScope ;

/* Variables and functions */
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void fscope_begin(FuncState *fs, FuncScope *bl, int flags)
{
  bl->nactvar = (uint8_t)fs->nactvar;
  bl->flags = flags;
  bl->vstart = fs->ls->vtop;
  bl->prev = fs->bl;
  fs->bl = bl;
  lua_assert(fs->freereg == fs->nactvar);
}