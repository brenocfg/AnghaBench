#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ps; } ;
struct TYPE_11__ {TYPE_1__ u; int /*<<< orphan*/  tag; } ;
typedef  TYPE_2__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  TSeq ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sib1 (TYPE_2__*) ; 
 TYPE_2__* sib2 (TYPE_2__*) ; 

__attribute__((used)) static TTree *seqaux (TTree *tree, TTree *sib, int sibsize) {
  tree->tag = TSeq; tree->u.ps = sibsize + 1;
  memcpy(sib1(tree), sib, sibsize * sizeof(TTree));
  return sib2(tree);
}