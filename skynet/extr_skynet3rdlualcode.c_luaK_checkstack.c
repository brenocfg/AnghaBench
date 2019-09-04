#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int freereg; TYPE_2__* f; int /*<<< orphan*/  ls; } ;
struct TYPE_6__ {TYPE_1__* sp; } ;
struct TYPE_5__ {int maxstacksize; } ;
typedef  TYPE_3__ FuncState ;

/* Variables and functions */
 int MAXREGS ; 
 int cast_byte (int) ; 
 int /*<<< orphan*/  luaX_syntaxerror (int /*<<< orphan*/ ,char*) ; 

void luaK_checkstack (FuncState *fs, int n) {
  int newstack = fs->freereg + n;
  if (newstack > fs->f->sp->maxstacksize) {
    if (newstack >= MAXREGS)
      luaX_syntaxerror(fs->ls,
        "function or expression needs too many registers");
    fs->f->sp->maxstacksize = cast_byte(newstack);
  }
}