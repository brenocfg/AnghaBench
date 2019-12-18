#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ RestoreMethod; int* Stamps; int Size; int /*<<< orphan*/  MaxOrder; int /*<<< orphan*/  OrderFall; scalar_t__ GlueCount; TYPE_1__* MaxContext; TYPE_1__* MinContext; } ;
struct TYPE_24__ {int Symbol; int Freq; } ;
struct TYPE_23__ {scalar_t__ NumStats; int Flags; int SummFreq; scalar_t__ Suffix; } ;
typedef  TYPE_1__* CTX_PTR ;
typedef  TYPE_2__ CPpmd_State ;
typedef  TYPE_3__ CPpmd8 ;

/* Variables and functions */
 int /*<<< orphan*/  CutOff (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExpandTextArea (TYPE_3__*) ; 
 int GetUsedMemory (TYPE_3__*) ; 
 TYPE_2__* ONE_STATE (TYPE_1__*) ; 
 scalar_t__ PPMD8_RESTORE_METHOD_FREEZE ; 
 scalar_t__ PPMD8_RESTORE_METHOD_RESTART ; 
 int /*<<< orphan*/  RESET_TEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Refresh (TYPE_3__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  RemoveBinContexts (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RestartModel (TYPE_3__*) ; 
 TYPE_2__* STATS (TYPE_1__*) ; 
 void* SUFFIX (TYPE_1__*) ; 
 int /*<<< orphan*/  SpecialFreeUnit (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void RestoreModel(CPpmd8 *p, CTX_PTR c1
    #ifdef PPMD8_FREEZE_SUPPORT
    , CTX_PTR fSuccessor
    #endif
    )
{
  CTX_PTR c;
  CPpmd_State *s;
  RESET_TEXT(0);
  for (c = p->MaxContext; c != c1; c = SUFFIX(c))
    if (--(c->NumStats) == 0)
    {
      s = STATS(c);
      c->Flags = (c->Flags & 0x10) + 0x08 * (s->Symbol >= 0x40);
      *ONE_STATE(c) = *s;
      SpecialFreeUnit(p, s);
      ONE_STATE(c)->Freq = (ONE_STATE(c)->Freq + 11) >> 3;
    }
    else
      Refresh(p, c, (c->NumStats+3) >> 1, 0);
 
  for (; c != p->MinContext; c = SUFFIX(c))
    if (!c->NumStats)
      ONE_STATE(c)->Freq -= ONE_STATE(c)->Freq >> 1;
    else if ((c->SummFreq += 4) > 128 + 4 * c->NumStats)
      Refresh(p, c, (c->NumStats + 2) >> 1, 1);

  #ifdef PPMD8_FREEZE_SUPPORT
  if (p->RestoreMethod > PPMD8_RESTORE_METHOD_FREEZE)
  {
    p->MaxContext = fSuccessor;
    p->GlueCount += !(p->Stamps[1] & 1);
  }
  else if (p->RestoreMethod == PPMD8_RESTORE_METHOD_FREEZE)
  {
    while (p->MaxContext->Suffix)
      p->MaxContext = SUFFIX(p->MaxContext);
    RemoveBinContexts(p, p->MaxContext, 0);
    p->RestoreMethod++;
    p->GlueCount = 0;
    p->OrderFall = p->MaxOrder;
  }
  else
  #endif
  if (p->RestoreMethod == PPMD8_RESTORE_METHOD_RESTART || GetUsedMemory(p) < (p->Size >> 1))
    RestartModel(p);
  else
  {
    while (p->MaxContext->Suffix)
      p->MaxContext = SUFFIX(p->MaxContext);
    do
    {
      CutOff(p, p->MaxContext, 0);
      ExpandTextArea(p);
    }
    while (GetUsedMemory(p) > 3 * (p->Size >> 2));
    p->GlueCount = 0;
    p->OrderFall = p->MaxOrder;
  }
}