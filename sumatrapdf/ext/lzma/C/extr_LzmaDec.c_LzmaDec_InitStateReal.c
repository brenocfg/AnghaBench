#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UInt32 ;
struct TYPE_4__ {size_t lc; size_t lp; } ;
struct TYPE_5__ {int* probs; int* reps; scalar_t__ needInitState; scalar_t__ state; TYPE_1__ prop; } ;
typedef  int CLzmaProb ;
typedef  TYPE_2__ CLzmaDec ;

/* Variables and functions */
 scalar_t__ LZMA_LIT_SIZE ; 
 size_t Literal ; 
 int kBitModelTotal ; 

__attribute__((used)) static void LzmaDec_InitStateReal(CLzmaDec *p)
{
  UInt32 numProbs = Literal + ((UInt32)LZMA_LIT_SIZE << (p->prop.lc + p->prop.lp));
  UInt32 i;
  CLzmaProb *probs = p->probs;
  for (i = 0; i < numProbs; i++)
    probs[i] = kBitModelTotal >> 1;
  p->reps[0] = p->reps[1] = p->reps[2] = p->reps[3] = 1;
  p->state = 0;
  p->needInitState = 0;
}