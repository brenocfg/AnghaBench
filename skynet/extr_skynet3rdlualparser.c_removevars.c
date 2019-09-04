#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  endpc; } ;
struct TYPE_11__ {int nactvar; int /*<<< orphan*/  pc; TYPE_3__* ls; } ;
struct TYPE_10__ {TYPE_2__* dyd; } ;
struct TYPE_8__ {int /*<<< orphan*/  n; } ;
struct TYPE_9__ {TYPE_1__ actvar; } ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 TYPE_6__* getlocvar (TYPE_4__*,int) ; 

__attribute__((used)) static void removevars (FuncState *fs, int tolevel) {
  fs->ls->dyd->actvar.n -= (fs->nactvar - tolevel);
  while (fs->nactvar > tolevel)
    getlocvar(fs, --fs->nactvar)->endpc = fs->pc;
}