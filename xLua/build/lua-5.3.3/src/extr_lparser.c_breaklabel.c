#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * arr; } ;
struct TYPE_10__ {TYPE_2__* dyd; TYPE_1__* fs; int /*<<< orphan*/  L; } ;
struct TYPE_9__ {TYPE_5__ label; } ;
struct TYPE_8__ {int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_3__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  findgotos (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaS_new (int /*<<< orphan*/ ,char*) ; 
 int newlabelentry (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void breaklabel (LexState *ls) {
  TString *n = luaS_new(ls->L, "break");
  int l = newlabelentry(ls, &ls->dyd->label, n, 0, ls->fs->pc);
  findgotos(ls, &ls->dyd->label.arr[l]);
}