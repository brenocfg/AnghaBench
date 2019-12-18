#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_17__ {void* tag; } ;
struct TYPE_15__ {int ps; } ;
struct TYPE_16__ {TYPE_1__ u; void* tag; } ;
typedef  TYPE_2__ TTree ;

/* Variables and functions */
 void* TChoice ; 
 void* TRep ; 
 void* TTrue ; 
 int /*<<< orphan*/  copyktable (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* getpatt (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_2__* newtree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ nullable (TYPE_2__*) ; 
 TYPE_2__* seqaux (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_2__* sib1 (TYPE_2__*) ; 
 TYPE_3__* sib2 (TYPE_2__*) ; 

__attribute__((used)) static int lp_star (lua_State *L) {
  int size1;
  int n = (int)luaL_checkinteger(L, 2);
  TTree *tree1 = getpatt(L, 1, &size1);
  if (n >= 0) {  /* seq tree1 (seq tree1 ... (seq tree1 (rep tree1))) */
    TTree *tree = newtree(L, (n + 1) * (size1 + 1));
    if (nullable(tree1))
      luaL_error(L, "loop body may accept empty string");
    while (n--)  /* repeat 'n' times */
      tree = seqaux(tree, tree1, size1);
    tree->tag = TRep;
    memcpy(sib1(tree), tree1, size1 * sizeof(TTree));
  }
  else {  /* choice (seq tree1 ... choice tree1 true ...) true */
    TTree *tree;
    n = -n;
    /* size = (choice + seq + tree1 + true) * n, but the last has no seq */
    tree = newtree(L, n * (size1 + 3) - 1);
    for (; n > 1; n--) {  /* repeat (n - 1) times */
      tree->tag = TChoice; tree->u.ps = n * (size1 + 3) - 2;
      sib2(tree)->tag = TTrue;
      tree = sib1(tree);
      tree = seqaux(tree, tree1, size1);
    }
    tree->tag = TChoice; tree->u.ps = size1 + 1;
    sib2(tree)->tag = TTrue;
    memcpy(sib1(tree), tree1, size1 * sizeof(TTree));
  }
  copyktable(L, 1);
  return 1;
}