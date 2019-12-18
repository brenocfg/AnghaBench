#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt16 ;
struct TYPE_11__ {int Size; int OrderFall; int MaxOrder; int RunLength; int InitRL; TYPE_3__** See; scalar_t__** BinSumm; TYPE_2__* FoundState; TYPE_1__* MinContext; scalar_t__ LoUnit; scalar_t__ HiUnit; TYPE_1__* MaxContext; scalar_t__ PrevSuccess; scalar_t__ GlueCount; scalar_t__ UnitsStart; scalar_t__ Text; scalar_t__ AlignOffset; scalar_t__ Base; int /*<<< orphan*/  FreeList; } ;
struct TYPE_10__ {int Shift; int Count; scalar_t__ Summ; } ;
struct TYPE_9__ {int Freq; scalar_t__ Symbol; } ;
struct TYPE_8__ {int NumStats; int SummFreq; int /*<<< orphan*/  Stats; scalar_t__ Suffix; } ;
typedef  int Int32 ;
typedef  TYPE_1__* CTX_PTR ;
typedef  TYPE_2__ CPpmd_State ;
typedef  TYPE_3__ CPpmd_See ;
typedef  TYPE_4__ CPpmd7 ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 scalar_t__ PPMD_BIN_SCALE ; 
 int PPMD_PERIOD_BITS ; 
 int /*<<< orphan*/  REF (TYPE_2__*) ; 
 int /*<<< orphan*/  SetSuccessor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ U2B (int) ; 
 int UNIT_SIZE ; 
 unsigned int* kInitBinEsc ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void RestartModel(CPpmd7 *p)
{
  unsigned i, k, m;

  memset(p->FreeList, 0, sizeof(p->FreeList));
  p->Text = p->Base + p->AlignOffset;
  p->HiUnit = p->Text + p->Size;
  p->LoUnit = p->UnitsStart = p->HiUnit - p->Size / 8 / UNIT_SIZE * 7 * UNIT_SIZE;
  p->GlueCount = 0;

  p->OrderFall = p->MaxOrder;
  p->RunLength = p->InitRL = -(Int32)((p->MaxOrder < 12) ? p->MaxOrder : 12) - 1;
  p->PrevSuccess = 0;

  p->MinContext = p->MaxContext = (CTX_PTR)(p->HiUnit -= UNIT_SIZE); /* AllocContext(p); */
  p->MinContext->Suffix = 0;
  p->MinContext->NumStats = 256;
  p->MinContext->SummFreq = 256 + 1;
  p->FoundState = (CPpmd_State *)p->LoUnit; /* AllocUnits(p, PPMD_NUM_INDEXES - 1); */
  p->LoUnit += U2B(256 / 2);
  p->MinContext->Stats = REF(p->FoundState);
  for (i = 0; i < 256; i++)
  {
    CPpmd_State *s = &p->FoundState[i];
    s->Symbol = (Byte)i;
    s->Freq = 1;
    SetSuccessor(s, 0);
  }

  for (i = 0; i < 128; i++)
    for (k = 0; k < 8; k++)
    {
      UInt16 *dest = p->BinSumm[i] + k;
      UInt16 val = (UInt16)(PPMD_BIN_SCALE - kInitBinEsc[k] / (i + 2));
      for (m = 0; m < 64; m += 8)
        dest[m] = val;
    }
  
  for (i = 0; i < 25; i++)
    for (k = 0; k < 16; k++)
    {
      CPpmd_See *s = &p->See[i][k];
      s->Summ = (UInt16)((5 * i + 10) << (s->Shift = PPMD_PERIOD_BITS - 4));
      s->Count = 4;
    }
}