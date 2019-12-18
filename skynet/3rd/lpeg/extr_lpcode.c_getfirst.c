#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int* cs; } ;
struct TYPE_15__ {int tag; } ;
typedef  TYPE_1__ TTree ;
typedef  TYPE_2__ Charset ;

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
 int /*<<< orphan*/  cs_complement (TYPE_2__*) ; 
 TYPE_2__* fullset ; 
 size_t i ; 
 int /*<<< orphan*/  loopset (size_t,int) ; 
 int /*<<< orphan*/  nullable (TYPE_1__*) ; 
 TYPE_1__* sib1 (TYPE_1__*) ; 
 TYPE_1__* sib2 (TYPE_1__*) ; 
 int /*<<< orphan*/  tocharset (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int getfirst (TTree *tree, const Charset *follow, Charset *firstset) {
 tailcall:
  switch (tree->tag) {
    case TChar: case TSet: case TAny: {
      tocharset(tree, firstset);
      return 0;
    }
    case TTrue: {
      loopset(i, firstset->cs[i] = follow->cs[i]);
      return 1;  /* accepts the empty string */
    }
    case TFalse: {
      loopset(i, firstset->cs[i] = 0);
      return 0;
    }
    case TChoice: {
      Charset csaux;
      int e1 = getfirst(sib1(tree), follow, firstset);
      int e2 = getfirst(sib2(tree), follow, &csaux);
      loopset(i, firstset->cs[i] |= csaux.cs[i]);
      return e1 | e2;
    }
    case TSeq: {
      if (!nullable(sib1(tree))) {
        /* when p1 is not nullable, p2 has nothing to contribute;
           return getfirst(sib1(tree), fullset, firstset); */
        tree = sib1(tree); follow = fullset; goto tailcall;
      }
      else {  /* FIRST(p1 p2, fl) = FIRST(p1, FIRST(p2, fl)) */
        Charset csaux;
        int e2 = getfirst(sib2(tree), follow, &csaux);
        int e1 = getfirst(sib1(tree), &csaux, firstset);
        if (e1 == 0) return 0;  /* 'e1' ensures that first can be used */
        else if ((e1 | e2) & 2)  /* one of the children has a matchtime? */
          return 2;  /* pattern has a matchtime capture */
        else return e2;  /* else depends on 'e2' */
      }
    }
    case TRep: {
      getfirst(sib1(tree), follow, firstset);
      loopset(i, firstset->cs[i] |= follow->cs[i]);
      return 1;  /* accept the empty string */
    }
    case TCapture: case TGrammar: case TRule: {
      /* return getfirst(sib1(tree), follow, firstset); */
      tree = sib1(tree); goto tailcall;
    }
    case TRunTime: {  /* function invalidates any follow info. */
      int e = getfirst(sib1(tree), fullset, firstset);
      if (e) return 2;  /* function is not "protected"? */
      else return 0;  /* pattern inside capture ensures first can be used */
    }
    case TCall: {
      /* return getfirst(sib2(tree), follow, firstset); */
      tree = sib2(tree); goto tailcall;
    }
    case TAnd: {
      int e = getfirst(sib1(tree), follow, firstset);
      loopset(i, firstset->cs[i] &= follow->cs[i]);
      return e;
    }
    case TNot: {
      if (tocharset(sib1(tree), firstset)) {
        cs_complement(firstset);
        return 1;
      }
      /* else go through */
    }
    case TBehind: {  /* instruction gives no new information */
      /* call 'getfirst' only to check for math-time captures */
      int e = getfirst(sib1(tree), follow, firstset);
      loopset(i, firstset->cs[i] = follow->cs[i]);  /* uses follow */
      return e | 1;  /* always can accept the empty string */
    }
    default: assert(0); return 0;
  }
}