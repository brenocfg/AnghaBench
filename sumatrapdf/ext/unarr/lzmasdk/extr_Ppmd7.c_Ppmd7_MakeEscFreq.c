#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
typedef  unsigned int UInt16 ;
struct TYPE_10__ {unsigned int NumStats; int SummFreq; } ;
struct TYPE_9__ {scalar_t__ NumStats; } ;
struct TYPE_7__ {unsigned int Summ; unsigned int Shift; } ;
struct TYPE_8__ {size_t* NS2Indx; int HiBitsFlag; TYPE_1__ DummySee; TYPE_4__* MinContext; TYPE_1__** See; } ;
typedef  TYPE_1__ CPpmd_See ;
typedef  TYPE_2__ CPpmd7 ;

/* Variables and functions */
 TYPE_3__* SUFFIX (TYPE_4__*) ; 

CPpmd_See *Ppmd7_MakeEscFreq(CPpmd7 *p, unsigned numMasked, UInt32 *escFreq)
{
  CPpmd_See *see;
  unsigned nonMasked = p->MinContext->NumStats - numMasked;
  if (p->MinContext->NumStats != 256)
  {
    see = p->See[p->NS2Indx[nonMasked - 1]] +
        (nonMasked < (unsigned)SUFFIX(p->MinContext)->NumStats - p->MinContext->NumStats) +
        2 * (p->MinContext->SummFreq < 11 * p->MinContext->NumStats) +
        4 * (numMasked > nonMasked) +
        p->HiBitsFlag;
    {
      unsigned r = (see->Summ >> see->Shift);
      see->Summ = (UInt16)(see->Summ - r);
      *escFreq = r + (r == 0);
    }
  }
  else
  {
    see = &p->DummySee;
    *escFreq = 1;
  }
  return see;
}