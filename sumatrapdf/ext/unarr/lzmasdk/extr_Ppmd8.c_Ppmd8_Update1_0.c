#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int PrevSuccess; int RunLength; TYPE_1__* FoundState; TYPE_2__* MinContext; } ;
struct TYPE_8__ {int SummFreq; } ;
struct TYPE_7__ {int Freq; } ;
typedef  TYPE_3__ CPpmd8 ;

/* Variables and functions */
 int MAX_FREQ ; 
 int /*<<< orphan*/  NextContext (TYPE_3__*) ; 
 int /*<<< orphan*/  Rescale (TYPE_3__*) ; 

void Ppmd8_Update1_0(CPpmd8 *p)
{
  p->PrevSuccess = (2 * p->FoundState->Freq >= p->MinContext->SummFreq);
  p->RunLength += p->PrevSuccess;
  p->MinContext->SummFreq += 4;
  if ((p->FoundState->Freq += 4) > MAX_FREQ)
    Rescale(p);
  NextContext(p);
}