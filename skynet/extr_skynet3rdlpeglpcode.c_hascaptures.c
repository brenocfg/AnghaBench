#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int tag; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
#define  TCall 132 
#define  TCapture 131 
#define  TOpenCall 130 
#define  TRule 129 
#define  TRunTime 128 
 int /*<<< orphan*/  assert (int) ; 
 int callrecursive (TYPE_1__*,int (*) (TYPE_1__*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * numsiblings ; 
 TYPE_1__* sib1 (TYPE_1__*) ; 
 TYPE_1__* sib2 (TYPE_1__*) ; 

int hascaptures (TTree *tree) {
 tailcall:
  switch (tree->tag) {
    case TCapture: case TRunTime:
      return 1;
    case TCall:
      return callrecursive(tree, hascaptures, 0);
    case TRule:  /* do not follow siblings */
      tree = sib1(tree); goto tailcall;
    case TOpenCall: assert(0);
    default: {
      switch (numsiblings[tree->tag]) {
        case 1:  /* return hascaptures(sib1(tree)); */
          tree = sib1(tree); goto tailcall;
        case 2:
          if (hascaptures(sib1(tree)))
            return 1;
          /* else return hascaptures(sib2(tree)); */
          tree = sib2(tree); goto tailcall;
        default: assert(numsiblings[tree->tag] == 0); return 0;
      }
    }
  }
}