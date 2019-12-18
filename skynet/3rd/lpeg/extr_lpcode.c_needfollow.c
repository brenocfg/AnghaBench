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
struct TYPE_7__ {int tag; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
#define  TAnd 142 
#define  TAny 141 
#define  TBehind 140 
#define  TCall 139 
#define  TCapture 138 
#define  TChar 137 
#define  TChoice 136 
#define  TFalse 135 
#define  TGrammar 134 
#define  TNot 133 
#define  TRep 132 
#define  TRunTime 131 
#define  TSeq 130 
#define  TSet 129 
#define  TTrue 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* sib1 (TYPE_1__*) ; 
 TYPE_1__* sib2 (TYPE_1__*) ; 

__attribute__((used)) static int needfollow (TTree *tree) {
 tailcall:
  switch (tree->tag) {
    case TChar: case TSet: case TAny:
    case TFalse: case TTrue: case TAnd: case TNot:
    case TRunTime: case TGrammar: case TCall: case TBehind:
      return 0;
    case TChoice: case TRep:
      return 1;
    case TCapture:
      tree = sib1(tree); goto tailcall;
    case TSeq:
      tree = sib2(tree); goto tailcall;
    default: assert(0); return 0;
  } 
}