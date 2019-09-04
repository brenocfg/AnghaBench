#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tag; } ;
struct TYPE_6__ {int cap; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  TCapture ; 
 int /*<<< orphan*/  TTrue ; 
 TYPE_2__* sib1 (TYPE_1__*) ; 

__attribute__((used)) static TTree *auxemptycap (TTree *tree, int cap) {
  tree->tag = TCapture;
  tree->cap = cap;
  sib1(tree)->tag = TTrue;
  return tree;
}