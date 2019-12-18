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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int cap; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  TCapture ; 
 int /*<<< orphan*/  addtonewktable (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* newroot1sib (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int capture_aux (lua_State *L, int cap, int labelidx) {
  TTree *tree = newroot1sib(L, TCapture);
  tree->cap = cap;
  tree->key = (labelidx == 0) ? 0 : addtonewktable(L, 1, labelidx);
  return 1;
}