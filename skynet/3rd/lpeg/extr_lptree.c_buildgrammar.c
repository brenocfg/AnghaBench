#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_12__ {int ps; } ;
struct TYPE_13__ {int cap; int /*<<< orphan*/  tag; TYPE_1__ u; scalar_t__ key; } ;
typedef  TYPE_2__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  TRule ; 
 int /*<<< orphan*/  TTrue ; 
 TYPE_2__* gettree (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mergektable (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 TYPE_2__* sib1 (TYPE_2__*) ; 
 TYPE_2__* sib2 (TYPE_2__*) ; 

__attribute__((used)) static void buildgrammar (lua_State *L, TTree *grammar, int frule, int n) {
  int i;
  TTree *nd = sib1(grammar);  /* auxiliary pointer to traverse the tree */
  for (i = 0; i < n; i++) {  /* add each rule into new tree */
    int ridx = frule + 2*i + 1;  /* index of i-th rule */
    int rulesize;
    TTree *rn = gettree(L, ridx, &rulesize);
    nd->tag = TRule;
    nd->key = 0;  /* will be fixed when rule is used */
    nd->cap = i;  /* rule number */
    nd->u.ps = rulesize + 1;  /* point to next rule */
    memcpy(sib1(nd), rn, rulesize * sizeof(TTree));  /* copy rule */
    mergektable(L, ridx, sib1(nd));  /* merge its ktable into new one */
    nd = sib2(nd);  /* move to next rule */
  }
  nd->tag = TTrue;  /* finish list of rules */
}