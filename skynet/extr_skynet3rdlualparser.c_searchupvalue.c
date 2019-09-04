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
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ Upvaldesc ;
struct TYPE_9__ {int nups; TYPE_2__* f; } ;
struct TYPE_7__ {TYPE_1__* sp; } ;
struct TYPE_6__ {TYPE_3__* upvalues; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 scalar_t__ eqstr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int searchupvalue (FuncState *fs, TString *name) {
  int i;
  Upvaldesc *up = fs->f->sp->upvalues;
  for (i = 0; i < fs->nups; i++) {
    if (eqstr(up[i].name, name)) return i;
  }
  return -1;  /* not found */
}