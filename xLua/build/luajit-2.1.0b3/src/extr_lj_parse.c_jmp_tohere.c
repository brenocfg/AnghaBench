#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  jpc; int /*<<< orphan*/  pc; int /*<<< orphan*/  lasttarget; } ;
typedef  TYPE_1__ FuncState ;
typedef  int /*<<< orphan*/  BCPos ;

/* Variables and functions */
 int /*<<< orphan*/  jmp_append (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jmp_tohere(FuncState *fs, BCPos list)
{
  fs->lasttarget = fs->pc;
  jmp_append(fs, &fs->jpc, list);
}