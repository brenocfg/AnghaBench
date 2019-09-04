#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_8__ {int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  TAny ; 
 int /*<<< orphan*/  TNot ; 
 int /*<<< orphan*/  TTrue ; 
 int /*<<< orphan*/  fillseq (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* newleaf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* newtree (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* sib1 (TYPE_1__*) ; 

__attribute__((used)) static TTree *numtree (lua_State *L, int n) {
  if (n == 0)
    return newleaf(L, TTrue);
  else {
    TTree *tree, *nd;
    if (n > 0)
      tree = nd = newtree(L, 2 * n - 1);
    else {  /* negative: code it as !(-n) */
      n = -n;
      tree = newtree(L, 2 * n);
      tree->tag = TNot;
      nd = sib1(tree);
    }
    fillseq(nd, TAny, n, NULL);  /* sequence of 'n' any's */
    return tree;
  }
}