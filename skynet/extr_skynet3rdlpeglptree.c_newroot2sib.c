#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {int ps; } ;
struct TYPE_10__ {int tag; TYPE_1__ u; } ;
typedef  TYPE_2__ TTree ;

/* Variables and functions */
 TYPE_2__* getpatt (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  joinktables (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 TYPE_2__* newtree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sib1 (TYPE_2__*) ; 
 int /*<<< orphan*/  sib2 (TYPE_2__*) ; 

__attribute__((used)) static TTree *newroot2sib (lua_State *L, int tag) {
  int s1, s2;
  TTree *tree1 = getpatt(L, 1, &s1);
  TTree *tree2 = getpatt(L, 2, &s2);
  TTree *tree = newtree(L, 1 + s1 + s2);  /* create new tree */
  tree->tag = tag;
  tree->u.ps =  1 + s1;
  memcpy(sib1(tree), tree1, s1 * sizeof(TTree));
  memcpy(sib2(tree), tree2, s2 * sizeof(TTree));
  joinktables(L, 1, sib2(tree), 2);
  return tree;
}