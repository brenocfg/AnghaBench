#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* FoundState; TYPE_1__* MinContext; } ;
struct TYPE_10__ {scalar_t__ Freq; } ;
struct TYPE_9__ {int SummFreq; } ;
typedef  TYPE_2__ CPpmd_State ;
typedef  TYPE_3__ CPpmd8 ;

/* Variables and functions */
 scalar_t__ MAX_FREQ ; 
 int /*<<< orphan*/  NextContext (TYPE_3__*) ; 
 int /*<<< orphan*/  Rescale (TYPE_3__*) ; 
 int /*<<< orphan*/  SwapStates (TYPE_2__*,TYPE_2__*) ; 

void Ppmd8_Update1(CPpmd8 *p)
{
  CPpmd_State *s = p->FoundState;
  s->Freq += 4;
  p->MinContext->SummFreq += 4;
  if (s[0].Freq > s[-1].Freq)
  {
    SwapStates(&s[0], &s[-1]);
    p->FoundState = --s;
    if (s->Freq > MAX_FREQ)
      Rescale(p);
  }
  NextContext(p);
}