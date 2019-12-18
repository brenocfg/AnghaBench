#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tag; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
#define  TAnd 143 
#define  TAny 142 
#define  TBehind 141 
#define  TCall 140 
#define  TCapture 139 
#define  TChar 138 
#define  TChoice 137 
#define  TFalse 136 
#define  TGrammar 135 
#define  TNot 134 
#define  TRep 133 
#define  TRule 132 
#define  TRunTime 131 
#define  TSeq 130 
#define  TSet 129 
#define  TTrue 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nofail (TYPE_1__*) ; 
 TYPE_1__* sib1 (TYPE_1__*) ; 
 TYPE_1__* sib2 (TYPE_1__*) ; 

__attribute__((used)) static int headfail (TTree *tree) {
 tailcall:
  switch (tree->tag) {
    case TChar: case TSet: case TAny: case TFalse:
      return 1;
    case TTrue: case TRep: case TRunTime: case TNot:
    case TBehind:
      return 0;
    case TCapture: case TGrammar: case TRule: case TAnd:
      tree = sib1(tree); goto tailcall;  /* return headfail(sib1(tree)); */
    case TCall:
      tree = sib2(tree); goto tailcall;  /* return headfail(sib2(tree)); */
    case TSeq:
      if (!nofail(sib2(tree))) return 0;
      /* else return headfail(sib1(tree)); */
      tree = sib1(tree); goto tailcall;
    case TChoice:
      if (!headfail(sib1(tree))) return 0;
      /* else return headfail(sib2(tree)); */
      tree = sib2(tree); goto tailcall;
    default: assert(0); return 0;
  }
}