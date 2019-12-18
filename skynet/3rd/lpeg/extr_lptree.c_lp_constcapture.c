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
struct TYPE_10__ {void* key; TYPE_1__ u; int /*<<< orphan*/  tag; int /*<<< orphan*/  cap; } ;
typedef  TYPE_2__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  Cconst ; 
 int /*<<< orphan*/  Cgroup ; 
 int /*<<< orphan*/  TCapture ; 
 int /*<<< orphan*/  TSeq ; 
 int /*<<< orphan*/  TTrue ; 
 void* addtoktable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  auxemptycap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newemptycapkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  newktable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  newleaf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* newtree (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* sib1 (TYPE_2__*) ; 
 TYPE_2__* sib2 (TYPE_2__*) ; 

__attribute__((used)) static int lp_constcapture (lua_State *L) {
  int i;
  int n = lua_gettop(L);  /* number of values */
  if (n == 0)  /* no values? */
    newleaf(L, TTrue);  /* no capture */
  else if (n == 1)
    newemptycapkey(L, Cconst, 1);  /* single constant capture */
  else {  /* create a group capture with all values */
    TTree *tree = newtree(L, 1 + 3 * (n - 1) + 2);
    newktable(L, n);  /* create a 'ktable' for new tree */
    tree->tag = TCapture;
    tree->cap = Cgroup;
    tree->key = 0;
    tree = sib1(tree);
    for (i = 1; i <= n - 1; i++) {
      tree->tag = TSeq;
      tree->u.ps = 3;  /* skip TCapture and its sibling */
      auxemptycap(sib1(tree), Cconst);
      sib1(tree)->key = addtoktable(L, i);
      tree = sib2(tree);
    }
    auxemptycap(tree, Cconst);
    tree->key = addtoktable(L, i);
  }
  return 1;
}