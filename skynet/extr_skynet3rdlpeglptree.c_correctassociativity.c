#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int ps; } ;
struct TYPE_14__ {scalar_t__ tag; TYPE_2__ u; } ;
struct TYPE_11__ {int ps; } ;
struct TYPE_13__ {scalar_t__ tag; TYPE_1__ u; } ;
typedef  TYPE_3__ TTree ;

/* Variables and functions */
 scalar_t__ TChoice ; 
 scalar_t__ TSeq ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (TYPE_3__*,TYPE_3__*,int) ; 
 TYPE_3__* sib1 (TYPE_3__*) ; 
 TYPE_4__* sib2 (TYPE_3__*) ; 

__attribute__((used)) static void correctassociativity (TTree *tree) {
  TTree *t1 = sib1(tree);
  assert(tree->tag == TChoice || tree->tag == TSeq);
  while (t1->tag == tree->tag) {
    int n1size = tree->u.ps - 1;  /* t1 == Op t11 t12 */
    int n11size = t1->u.ps - 1;
    int n12size = n1size - n11size - 1;
    memmove(sib1(tree), sib1(t1), n11size * sizeof(TTree)); /* move t11 */
    tree->u.ps = n11size + 1;
    sib2(tree)->tag = tree->tag;
    sib2(tree)->u.ps = n12size + 1;
  }
}