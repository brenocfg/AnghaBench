#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int OrderFall; scalar_t__ RestoreMethod; TYPE_1__* Text; TYPE_2__* FoundState; TYPE_1__* MaxContext; } ;
struct TYPE_22__ {scalar_t__ Symbol; int Freq; } ;
struct TYPE_21__ {int SummFreq; scalar_t__ NumStats; int /*<<< orphan*/  Suffix; } ;
typedef  TYPE_1__* CTX_PTR ;
typedef  scalar_t__ CPpmd_Void_Ref ;
typedef  TYPE_2__ CPpmd_State ;
typedef  TYPE_3__ CPpmd8 ;

/* Variables and functions */
 TYPE_1__* CTX (scalar_t__) ; 
 TYPE_1__* CreateSuccessors (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  False ; 
 int MAX_FREQ ; 
 TYPE_2__* ONE_STATE (TYPE_1__*) ; 
 int /*<<< orphan*/  PPMD8_MAX_ORDER ; 
 scalar_t__ PPMD8_RESTORE_METHOD_FREEZE ; 
 scalar_t__ REF (TYPE_1__*) ; 
 int /*<<< orphan*/  RESET_TEXT (int) ; 
 TYPE_2__* STATS (TYPE_1__*) ; 
 scalar_t__ SUCCESSOR (TYPE_2__*) ; 
 TYPE_1__* SUFFIX (TYPE_1__*) ; 
 int /*<<< orphan*/  SetSuccessor (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static CTX_PTR ReduceOrder(CPpmd8 *p, CPpmd_State *s1, CTX_PTR c)
{
  CPpmd_State *s = NULL;
  CTX_PTR c1 = c;
  CPpmd_Void_Ref upBranch = REF(p->Text);
  
  #ifdef PPMD8_FREEZE_SUPPORT
  /* The BUG in Shkarin's code was fixed: ps could overflow in CUT_OFF mode. */
  CPpmd_State *ps[PPMD8_MAX_ORDER + 1];
  unsigned numPs = 0;
  ps[numPs++] = p->FoundState;
  #endif

  SetSuccessor(p->FoundState, upBranch);
  p->OrderFall++;

  for (;;)
  {
    if (s1)
    {
      c = SUFFIX(c);
      s = s1;
      s1 = NULL;
    }
    else
    {
      if (!c->Suffix)
      {
        #ifdef PPMD8_FREEZE_SUPPORT
        if (p->RestoreMethod > PPMD8_RESTORE_METHOD_FREEZE)
        {
          do { SetSuccessor(ps[--numPs], REF(c)); } while (numPs);
          RESET_TEXT(1);
          p->OrderFall = 1;
        }
        #endif
        return c;
      }
      c = SUFFIX(c);
      if (c->NumStats)
      {
        if ((s = STATS(c))->Symbol != p->FoundState->Symbol)
          do { s++; } while (s->Symbol != p->FoundState->Symbol);
        if (s->Freq < MAX_FREQ - 9)
        {
          s->Freq += 2;
          c->SummFreq += 2;
        }
      }
      else
      {
        s = ONE_STATE(c);
        s->Freq += (s->Freq < 32);
      }
    }
    if (SUCCESSOR(s))
      break;
    #ifdef PPMD8_FREEZE_SUPPORT
    ps[numPs++] = s;
    #endif
    SetSuccessor(s, upBranch);
    p->OrderFall++;
  }
  
  #ifdef PPMD8_FREEZE_SUPPORT
  if (p->RestoreMethod > PPMD8_RESTORE_METHOD_FREEZE)
  {
    c = CTX(SUCCESSOR(s));
    do { SetSuccessor(ps[--numPs], REF(c)); } while (numPs);
    RESET_TEXT(1);
    p->OrderFall = 1;
    return c;
  }
  else
  #endif
  if (SUCCESSOR(s) <= upBranch)
  {
    CTX_PTR successor;
    CPpmd_State *s1 = p->FoundState;
    p->FoundState = s;

    successor = CreateSuccessors(p, False, NULL, c);
    if (successor == NULL)
      SetSuccessor(s, 0);
    else
      SetSuccessor(s, REF(successor));
    p->FoundState = s1;
  }
  
  if (p->OrderFall == 1 && c1 == p->MaxContext)
  {
    SetSuccessor(p->FoundState, SUCCESSOR(s));
    p->Text--;
  }
  if (SUCCESSOR(s) == 0)
    return NULL;
  return CTX(SUCCESSOR(s));
}