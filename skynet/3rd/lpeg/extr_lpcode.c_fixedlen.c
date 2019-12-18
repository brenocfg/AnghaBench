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
#define  TAnd 144 
#define  TAny 143 
#define  TBehind 142 
#define  TCall 141 
#define  TCapture 140 
#define  TChar 139 
#define  TChoice 138 
#define  TFalse 137 
#define  TGrammar 136 
#define  TNot 135 
#define  TOpenCall 134 
#define  TRep 133 
#define  TRule 132 
#define  TRunTime 131 
#define  TSeq 130 
#define  TSet 129 
#define  TTrue 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int callrecursive (TYPE_1__*,int (*) (TYPE_1__*),int) ; 
 TYPE_1__* sib1 (TYPE_1__*) ; 
 TYPE_1__* sib2 (TYPE_1__*) ; 

int fixedlen (TTree *tree) {
  int len = 0;  /* to accumulate in tail calls */
 tailcall:
  switch (tree->tag) {
    case TChar: case TSet: case TAny:
      return len + 1;
    case TFalse: case TTrue: case TNot: case TAnd: case TBehind:
      return len;
    case TRep: case TRunTime: case TOpenCall:
      return -1;
    case TCapture: case TRule: case TGrammar:
      /* return fixedlen(sib1(tree)); */
      tree = sib1(tree); goto tailcall;
    case TCall: {
      int n1 = callrecursive(tree, fixedlen, -1);
      if (n1 < 0)
        return -1;
      else
        return len + n1;
    }
    case TSeq: {
      int n1 = fixedlen(sib1(tree));
      if (n1 < 0)
        return -1;
      /* else return fixedlen(sib2(tree)) + len; */
      len += n1; tree = sib2(tree); goto tailcall;
    }
    case TChoice: {
      int n1 = fixedlen(sib1(tree));
      int n2 = fixedlen(sib2(tree));
      if (n1 != n2 || n1 < 0)
        return -1;
      else
        return len + n1;
    }
    default: assert(0); return 0;
  };
}