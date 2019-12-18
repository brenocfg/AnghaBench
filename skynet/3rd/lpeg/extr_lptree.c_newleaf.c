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
struct TYPE_4__ {int tag; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 TYPE_1__* newtree (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static TTree *newleaf (lua_State *L, int tag) {
  TTree *tree = newtree(L, 1);
  tree->tag = tag;
  return tree;
}