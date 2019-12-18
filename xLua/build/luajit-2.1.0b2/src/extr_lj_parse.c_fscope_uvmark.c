#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nactvar; int /*<<< orphan*/  flags; struct TYPE_5__* prev; } ;
struct TYPE_4__ {TYPE_2__* bl; } ;
typedef  TYPE_1__ FuncState ;
typedef  TYPE_2__ FuncScope ;
typedef  scalar_t__ BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  FSCOPE_UPVAL ; 

__attribute__((used)) static void fscope_uvmark(FuncState *fs, BCReg level)
{
  FuncScope *bl;
  for (bl = fs->bl; bl && bl->nactvar > level; bl = bl->prev)
    ;
  if (bl)
    bl->flags |= FSCOPE_UPVAL;
}