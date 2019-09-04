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
struct TYPE_4__ {int Cf; int Of; int Zf; int Sf; int /*<<< orphan*/  Pf; } ;
struct TYPE_5__ {TYPE_1__ Flags; } ;
typedef  TYPE_2__* PFAST486_STATE ;
typedef  int INT ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  Fast486CalculateParity (int) ; 

__attribute__((used)) static
inline
ULONG
Fast486RotateOperation(PFAST486_STATE State,
                       INT Operation,
                       ULONG Value,
                       UCHAR Bits,
                       UCHAR Count)
{
    ULONG HighestBit = 1 << (Bits - 1);
    ULONG MaxValue = HighestBit | (HighestBit - 1);
    ULONG Result;

    /* Normalize the count */
    Count &= 0x1F;

    if ((Operation == 2) || (Operation == 3)) Count %= Bits + 1;

    /* If the count is zero, do nothing */
    if (Count == 0) return Value;

    /* Check which operation is this */
    switch (Operation)
    {
        /* ROL */
        case 0:
        {
            Count %= Bits;
            Result = (Value << Count) | (Value >> (Bits - Count));

            /* Update CF and OF */
            State->Flags.Cf = Result & 1;
            if (Count == 1) State->Flags.Of = State->Flags.Cf
                                              ^ ((Result & HighestBit) != 0);

            break;
        }

        /* ROR */
        case 1:
        {
            Count %= Bits;
            Result = (Value >> Count) | (Value << (Bits - Count));

            /* Update CF and OF */
            State->Flags.Cf = ((Result & HighestBit) != 0);
            if (Count == 1) State->Flags.Of = State->Flags.Cf
                                              ^ ((Result & (HighestBit >> 1)) != 0);

            break;
        }

        /* RCL */
        case 2:
        {
            Result = (Value << Count) | (State->Flags.Cf << (Count - 1));

            /* Complete the calculation, but make sure we don't shift by too much */
            if ((Bits - Count) < 31) Result |= Value >> (Bits - Count + 1);

            /* Update CF and OF */
            State->Flags.Cf = ((Value & (1 << (Bits - Count))) != 0);
            if (Count == 1) State->Flags.Of = State->Flags.Cf ^ ((Result & HighestBit) != 0);

            break;
        }

        /* RCR */
        case 3:
        {
            /* Update OF */
            if (Count == 1) State->Flags.Of = State->Flags.Cf ^ ((Value & HighestBit) != 0);

            Result = (Value >> Count) | (State->Flags.Cf << (Bits - Count));

            /* Complete the calculation, but make sure we don't shift by too much */
            if ((Bits - Count) < 31) Result |= Value << (Bits - Count + 1);

            /* Update CF */
            State->Flags.Cf = ((Value & (1 << (Count - 1))) != 0);

            break;
        }

        /* SHL/SAL */
        case 4:
        case 6:
        {
            Result = Value << Count;

            /* Update CF and OF */
            State->Flags.Cf = ((Value & (1 << (Bits - Count))) != 0);
            if (Count == 1) State->Flags.Of = State->Flags.Cf
                                              ^ ((Result & HighestBit) != 0);

            break;
        }

        /* SHR */
        case 5:
        {
            Result = Value >> Count;

            /* Update CF and OF */
            State->Flags.Cf = ((Value & (1 << (Count - 1))) != 0);
            if (Count == 1) State->Flags.Of = ((Value & HighestBit) != 0);

            break;
        }

        /* SAR */
        case 7:
        {
            Result = Value >> Count;

            /* Fill the top Count bits with the sign bit */
            if (Value & HighestBit) Result |= ((1 << Count) - 1) << (Bits - Count);

            /* Update CF and OF */
            State->Flags.Cf = ((Value & (1 << (Count - 1))) != 0);
            if (Count == 1) State->Flags.Of = FALSE;

            break;
        }
    }

    if (Operation >= 4)
    {
        /* Update ZF, SF and PF */
        State->Flags.Zf = ((Result & MaxValue) == 0);
        State->Flags.Sf = ((Result & HighestBit) != 0);
        State->Flags.Pf = Fast486CalculateParity(Result);
    }

    /* Return the result */
    return Result;
}