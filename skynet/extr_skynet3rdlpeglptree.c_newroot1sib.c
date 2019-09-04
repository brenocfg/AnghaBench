#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int tag; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  copyktable (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* getpatt (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 TYPE_1__* newtree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sib1 (TYPE_1__*) ; 

__attribute__((used)) static TTree *newroot1sib (lua_State *L, int tag) {
  int s1;
  TTree *tree1 = getpatt(L, 1, &s1);
  TTree *tree = newtree(L, 1 + s1);  /* create new tree */
  tree->tag = tag;
  memcpy(sib1(tree), tree1, s1 * sizeof(TTree));
  copyktable(L, 1);
  return tree;
}