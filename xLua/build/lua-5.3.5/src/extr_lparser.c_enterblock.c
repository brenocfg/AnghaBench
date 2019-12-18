#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lu_byte ;
struct TYPE_14__ {scalar_t__ nactvar; struct TYPE_14__* previous; scalar_t__ upval; int /*<<< orphan*/  firstgoto; int /*<<< orphan*/  firstlabel; int /*<<< orphan*/  isloop; } ;
struct TYPE_13__ {scalar_t__ nactvar; scalar_t__ freereg; TYPE_6__* bl; TYPE_4__* ls; } ;
struct TYPE_12__ {TYPE_3__* dyd; } ;
struct TYPE_10__ {int /*<<< orphan*/  n; } ;
struct TYPE_9__ {int /*<<< orphan*/  n; } ;
struct TYPE_11__ {TYPE_2__ gt; TYPE_1__ label; } ;
typedef  TYPE_5__ FuncState ;
typedef  TYPE_6__ BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void enterblock (FuncState *fs, BlockCnt *bl, lu_byte isloop) {
  bl->isloop = isloop;
  bl->nactvar = fs->nactvar;
  bl->firstlabel = fs->ls->dyd->label.n;
  bl->firstgoto = fs->ls->dyd->gt.n;
  bl->upval = 0;
  bl->previous = fs->bl;
  fs->bl = bl;
  lua_assert(fs->freereg == fs->nactvar);
}