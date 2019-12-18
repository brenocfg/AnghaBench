#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
typedef  unsigned int UInt16 ;
struct TYPE_7__ {int Symbol; unsigned int Freq; } ;
struct TYPE_6__ {unsigned int NumStats; int SummFreq; int Flags; int /*<<< orphan*/  Stats; } ;
typedef  TYPE_1__* CTX_PTR ;
typedef  TYPE_2__ CPpmd_State ;
typedef  int /*<<< orphan*/  CPpmd8 ;
typedef  void* Byte ;

/* Variables and functions */
 int /*<<< orphan*/  REF (TYPE_2__*) ; 
 int /*<<< orphan*/  STATS (TYPE_1__*) ; 
 scalar_t__ ShrinkUnits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void Refresh(CPpmd8 *p, CTX_PTR ctx, unsigned oldNU, unsigned scale)
{
  unsigned i = ctx->NumStats, escFreq, sumFreq, flags;
  CPpmd_State *s = (CPpmd_State *)ShrinkUnits(p, STATS(ctx), oldNU, (i + 2) >> 1);
  ctx->Stats = REF(s);
  #ifdef PPMD8_FREEZE_SUPPORT
  /* fixed over Shkarin's code. Fixed code is not compatible with original code for some files in FREEZE mode. */
  scale |= (ctx->SummFreq >= ((UInt32)1 << 15));
  #endif
  flags = (ctx->Flags & (0x10 + 0x04 * scale)) + 0x08 * (s->Symbol >= 0x40);
  escFreq = ctx->SummFreq - s->Freq;
  sumFreq = (s->Freq = (Byte)((s->Freq + scale) >> scale));
  do
  {
    escFreq -= (++s)->Freq;
    sumFreq += (s->Freq = (Byte)((s->Freq + scale) >> scale));
    flags |= 0x08 * (s->Symbol >= 0x40);
  }
  while (--i);
  ctx->SummFreq = (UInt16)(sumFreq + ((escFreq + scale) >> scale));
  ctx->Flags = (Byte)flags;
}