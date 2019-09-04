#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_19__ {int* cs; } ;
struct TYPE_17__ {int ps; } ;
struct TYPE_18__ {int /*<<< orphan*/  tag; TYPE_1__ u; } ;
typedef  TYPE_2__ TTree ;
typedef  TYPE_3__ Charset ;

/* Variables and functions */
 int /*<<< orphan*/  TNot ; 
 int /*<<< orphan*/  TSeq ; 
 TYPE_2__* getpatt (int /*<<< orphan*/ *,int,int*) ; 
 size_t i ; 
 int /*<<< orphan*/  joinktables (int /*<<< orphan*/ *,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  loopset (size_t,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_2__* newcharset (int /*<<< orphan*/ *) ; 
 TYPE_2__* newtree (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* sib1 (TYPE_2__*) ; 
 TYPE_2__* sib2 (TYPE_2__*) ; 
 scalar_t__ tocharset (TYPE_2__*,TYPE_3__*) ; 
 int* treebuffer (TYPE_2__*) ; 

__attribute__((used)) static int lp_sub (lua_State *L) {
  Charset st1, st2;
  int s1, s2;
  TTree *t1 = getpatt(L, 1, &s1);
  TTree *t2 = getpatt(L, 2, &s2);
  if (tocharset(t1, &st1) && tocharset(t2, &st2)) {
    TTree *t = newcharset(L);
    loopset(i, treebuffer(t)[i] = st1.cs[i] & ~st2.cs[i]);
  }
  else {
    TTree *tree = newtree(L, 2 + s1 + s2);
    tree->tag = TSeq;  /* sequence of... */
    tree->u.ps =  2 + s2;
    sib1(tree)->tag = TNot;  /* ...not... */
    memcpy(sib1(sib1(tree)), t2, s2 * sizeof(TTree));  /* ...t2 */
    memcpy(sib2(tree), t1, s1 * sizeof(TTree));  /* ... and t1 */
    joinktables(L, 1, sib1(tree), 2);
  }
  return 1;
}