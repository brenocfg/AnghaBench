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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  addtonewktable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* auxemptycap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  newtree (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static TTree *newemptycapkey (lua_State *L, int cap, int idx) {
  TTree *tree = auxemptycap(newtree(L, 2), cap);
  tree->key = addtonewktable(L, 0, idx);
  return tree;
}