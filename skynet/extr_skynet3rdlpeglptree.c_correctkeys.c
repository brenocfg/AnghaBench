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
struct TYPE_7__ {int tag; int key; int /*<<< orphan*/  cap; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  Carg ; 
 int /*<<< orphan*/  Cnum ; 
#define  TCall 132 
#define  TCapture 131 
#define  TOpenCall 130 
#define  TRule 129 
#define  TRunTime 128 
 int /*<<< orphan*/  assert (int) ; 
 int* numsiblings ; 
 TYPE_1__* sib1 (TYPE_1__*) ; 
 TYPE_1__* sib2 (TYPE_1__*) ; 

__attribute__((used)) static void correctkeys (TTree *tree, int n) {
  if (n == 0) return;  /* no correction? */
 tailcall:
  switch (tree->tag) {
    case TOpenCall: case TCall: case TRunTime: case TRule: {
      if (tree->key > 0)
        tree->key += n;
      break;
    }
    case TCapture: {
      if (tree->key > 0 && tree->cap != Carg && tree->cap != Cnum)
        tree->key += n;
      break;
    }
    default: break;
  }
  switch (numsiblings[tree->tag]) {
    case 1:  /* correctkeys(sib1(tree), n); */
      tree = sib1(tree); goto tailcall;
    case 2:
      correctkeys(sib1(tree), n);
      tree = sib2(tree); goto tailcall;  /* correctkeys(sib2(tree), n); */
    default: assert(numsiblings[tree->tag] == 0); break;
  }
}