#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int WriteStatus; int ReadWriteMode; int CountRegister; int ReloadValue; int CurrentValue; scalar_t__ Bcd; } ;
typedef  int* LPBYTE ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__* PitChannels ; 
 int WRITE_PIT_VALUE (TYPE_1__,int) ; 

__attribute__((used)) static VOID PitWriteData(BYTE Channel, BYTE Value)
{
    LPBYTE ReadWriteMode = NULL;

    if (PitChannels[Channel].WriteStatus == 0x00)
    {
        PitChannels[Channel].WriteStatus = PitChannels[Channel].ReadWriteMode;
    }

    ASSERT(PitChannels[Channel].WriteStatus != 0);

    ReadWriteMode = &PitChannels[Channel].WriteStatus;

    if (*ReadWriteMode & 1)
    {
        /* Write LSB */
        *ReadWriteMode &= ~1;
        PitChannels[Channel].CountRegister &= 0xFF00;
        PitChannels[Channel].CountRegister |= Value;
    }
    else if (*ReadWriteMode & 2)
    {
        /* Write MSB */
        *ReadWriteMode &= ~2;
        PitChannels[Channel].CountRegister &= 0x00FF;
        PitChannels[Channel].CountRegister |= Value << 8;
    }

    /* ReadWriteMode went to zero: we are going to load the new count */
    if (*ReadWriteMode == 0x00)
    {
        if (PitChannels[Channel].CountRegister == 0x0000)
        {
            /* Wrap around to the highest count */
            if (PitChannels[Channel].Bcd)
                PitChannels[Channel].CountRegister = 9999;
            else
                PitChannels[Channel].CountRegister = 0xFFFF; // 0x10000; // 65536
        }

        /* Convert the current value from BCD if needed */
        PitChannels[Channel].CountRegister =
            WRITE_PIT_VALUE(PitChannels[Channel], PitChannels[Channel].CountRegister);
        PitChannels[Channel].ReloadValue = PitChannels[Channel].CountRegister;

        /* Reload now the new count */
        PitChannels[Channel].CurrentValue = PitChannels[Channel].ReloadValue;
    }
}