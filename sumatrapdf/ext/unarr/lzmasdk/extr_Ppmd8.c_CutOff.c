#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int* UnitsStart; unsigned int MaxOrder; } ;
struct TYPE_26__ {int Symbol; int Freq; } ;
struct TYPE_25__ {int NumStats; int Flags; int SummFreq; int /*<<< orphan*/  Stats; } ;
typedef  TYPE_1__* CTX_PTR ;
typedef  int /*<<< orphan*/  CPpmd_Void_Ref ;
typedef  TYPE_2__ CPpmd_State ;
typedef  TYPE_3__ CPpmd8 ;
typedef  int Byte ;

/* Variables and functions */
 TYPE_1__* CTX (scalar_t__) ; 
 int /*<<< orphan*/  FreeUnits (TYPE_3__*,TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  MoveUnitsUp (TYPE_3__*,TYPE_2__*,unsigned int) ; 
 TYPE_2__* ONE_STATE (TYPE_1__*) ; 
 scalar_t__ Ppmd8_GetPtr (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  REF (TYPE_1__*) ; 
 int /*<<< orphan*/  Refresh (TYPE_3__*,TYPE_1__*,unsigned int,int) ; 
 TYPE_2__* STATS (TYPE_1__*) ; 
 int /*<<< orphan*/  STATS_REF (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESSOR (TYPE_2__*) ; 
 int /*<<< orphan*/  SetSuccessor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpecialFreeUnit (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SwapStates (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static CPpmd_Void_Ref CutOff(CPpmd8 *p, CTX_PTR ctx, unsigned order)
{
  int i;
  unsigned tmp;
  CPpmd_State *s;
  
  if (!ctx->NumStats)
  {
    s = ONE_STATE(ctx);
    if ((Byte *)Ppmd8_GetPtr(p, SUCCESSOR(s)) >= p->UnitsStart)
    {
      if (order < p->MaxOrder)
        SetSuccessor(s, CutOff(p, CTX(SUCCESSOR(s)), order + 1));
      else
        SetSuccessor(s, 0);
      if (SUCCESSOR(s) || order <= 9) /* O_BOUND */
        return REF(ctx);
    }
    SpecialFreeUnit(p, ctx);
    return 0;
  }

  ctx->Stats = STATS_REF(MoveUnitsUp(p, STATS(ctx), tmp = ((unsigned)ctx->NumStats + 2) >> 1));

  for (s = STATS(ctx) + (i = ctx->NumStats); s >= STATS(ctx); s--)
    if ((Byte *)Ppmd8_GetPtr(p, SUCCESSOR(s)) < p->UnitsStart)
    {
      CPpmd_State *s2 = STATS(ctx) + (i--);
      SetSuccessor(s, 0);
      SwapStates(s, s2);
    }
    else if (order < p->MaxOrder)
      SetSuccessor(s, CutOff(p, CTX(SUCCESSOR(s)), order + 1));
    else
      SetSuccessor(s, 0);
    
  if (i != ctx->NumStats && order)
  {
    ctx->NumStats = (Byte)i;
    s = STATS(ctx);
    if (i < 0)
    {
      FreeUnits(p, s, tmp);
      SpecialFreeUnit(p, ctx);
      return 0;
    }
    if (i == 0)
    {
      ctx->Flags = (ctx->Flags & 0x10) + 0x08 * (s->Symbol >= 0x40);
      *ONE_STATE(ctx) = *s;
      FreeUnits(p, s, tmp);
      ONE_STATE(ctx)->Freq = (Byte)((unsigned)ONE_STATE(ctx)->Freq + 11) >> 3;
    }
    else
      Refresh(p, ctx, tmp, ctx->SummFreq > 16 * i);
  }
  return REF(ctx);
}