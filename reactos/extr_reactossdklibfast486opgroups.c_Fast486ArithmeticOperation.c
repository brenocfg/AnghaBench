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
typedef  int ULONG ;
typedef  int UCHAR ;
struct TYPE_4__ {int Cf; int Of; int Af; int Zf; int Sf; int /*<<< orphan*/  Pf; } ;
struct TYPE_5__ {TYPE_1__ Flags; } ;
typedef  TYPE_2__* PFAST486_STATE ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (void*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  Fast486CalculateParity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOBYTE (int) ; 

__attribute__((used)) static
inline
ULONG
Fast486ArithmeticOperation(PFAST486_STATE State,
                           INT Operation,
                           ULONG FirstValue,
                           ULONG SecondValue,
                           UCHAR Bits)
{
    ULONG Result;
    ULONG SignFlag = 1 << (Bits - 1);
    ULONG MaxValue = (SignFlag - 1) | SignFlag;

    /* Make sure the values don't exceed the maximum for their size */
    FirstValue &= MaxValue;
    SecondValue &= MaxValue;

    /* Check which operation is this */
    switch (Operation)
    {
        /* ADD */
        case 0:
        {
            Result = (FirstValue + SecondValue) & MaxValue;

            /* Update CF, OF and AF */
            State->Flags.Cf = (Result < FirstValue) && (Result < SecondValue);
            State->Flags.Of = ((FirstValue & SignFlag) == (SecondValue & SignFlag))
                              && ((FirstValue & SignFlag) != (Result & SignFlag));
            State->Flags.Af = ((((FirstValue & 0x0F) + (SecondValue & 0x0F)) & 0x10) != 0);

            break;
        }

        /* OR */
        case 1:
        {
            Result = FirstValue | SecondValue;
            State->Flags.Cf = State->Flags.Of = FALSE;
            break;
        }

        /* ADC */
        case 2:
        {
            INT Carry = State->Flags.Cf ? 1 : 0;

            Result = (FirstValue + SecondValue + Carry) & MaxValue;

            /* Update CF, OF and AF */
            State->Flags.Cf = ((SecondValue == MaxValue) && (Carry == 1))
                              || ((Result < FirstValue) && (Result < (SecondValue + Carry)));
            State->Flags.Of = ((FirstValue & SignFlag) == (SecondValue & SignFlag))
                              && ((FirstValue & SignFlag) != (Result & SignFlag));
            State->Flags.Af = ((FirstValue ^ SecondValue ^ Result) & 0x10) != 0;

            break;
        }

        /* SBB */
        case 3:
        {
            INT Carry = State->Flags.Cf ? 1 : 0;

            Result = (FirstValue - SecondValue - Carry) & MaxValue;

            /* Update CF, OF and AF */
            State->Flags.Cf = Carry
                              ? (FirstValue <= SecondValue)
                              : (FirstValue < SecondValue);
            State->Flags.Of = ((FirstValue & SignFlag) != (SecondValue & SignFlag))
                              && ((FirstValue & SignFlag) != (Result & SignFlag));
            State->Flags.Af = ((FirstValue ^ SecondValue ^ Result) & 0x10) != 0;

            break;
        }

        /* AND */
        case 4:
        {
            Result = FirstValue & SecondValue;
            State->Flags.Cf = State->Flags.Of = FALSE;
            break;
        }

        /* SUB or CMP */
        case 5:
        case 7:
        {
            Result = (FirstValue - SecondValue) & MaxValue;

            /* Update CF, OF and AF */
            State->Flags.Cf = (FirstValue < SecondValue);
            State->Flags.Of = ((FirstValue & SignFlag) != (SecondValue & SignFlag))
                              && ((FirstValue & SignFlag) != (Result & SignFlag));
            State->Flags.Af = (FirstValue & 0x0F) < (SecondValue & 0x0F);

            break;
        }

        /* XOR */
        case 6:
        {
            Result = FirstValue ^ SecondValue;
            State->Flags.Cf = State->Flags.Of = FALSE;
            break;
        }

        default:
        {
            /* Shouldn't happen */
            ASSERT(FALSE);
        }
    }

    /* Update ZF, SF and PF */
    State->Flags.Zf = (Result == 0);
    State->Flags.Sf = ((Result & SignFlag) != 0);
    State->Flags.Pf = Fast486CalculateParity(LOBYTE(Result));

    /* Return the result */
    return Result;
}