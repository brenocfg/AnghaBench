#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int srr1; } ;

/* Variables and functions */
 int Continue ; 
 int /*<<< orphan*/  DataInAddr ; 
 int* DataInBuffer ; 
 int GDB_SAVE_SIZE ; 
 int /*<<< orphan*/  PacketEmpty () ; 
 int /*<<< orphan*/  PacketFinish () ; 
 int /*<<< orphan*/  PacketOk () ; 
 void* PacketReadHexNumber (int) ; 
 int /*<<< orphan*/  PacketStart () ; 
 int /*<<< orphan*/  PacketWriteHexNumber (char,int) ; 
 int /*<<< orphan*/  PacketWriteSignal (int /*<<< orphan*/ ) ; 
 TYPE_1__* RegisterSaveArea ; 
 int /*<<< orphan*/  Signal ; 
 int /*<<< orphan*/  marker () ; 

void GotPacket()
{
    int i, memaddr, memsize;

    Continue = 0;
    switch (DataInBuffer[DataInAddr++])
    {
    case 'g':
        PacketStart();
        for (i = 0; i < GDB_SAVE_SIZE; i++)
        {
            PacketWriteHexNumber(((int *)RegisterSaveArea)[i], 8);
        }
        PacketFinish();
        break;

    case 'G':
        for (i = 0; i < sizeof(*RegisterSaveArea) / sizeof(int); i++)
        {
            ((int *)RegisterSaveArea)[i] = PacketReadHexNumber(8);
        }
        PacketOk();
        break;

    case 'm':
        memaddr = PacketReadHexNumber(8);
        DataInAddr++;
        memsize = PacketReadHexNumber(8);
        PacketStart();
        while(memsize-- > 0)
        {
            PacketWriteHexNumber(*((char *)memaddr++), 2);
        }
        PacketFinish();
        break;

    case 'M':
        memaddr = PacketReadHexNumber(8);
        DataInAddr++;
        memsize = PacketReadHexNumber(8);
        DataInAddr++;
        while(memsize-- > 0)
        {
            *((char *)memaddr++) = PacketReadHexNumber(2);
        }
        PacketOk();
        break;

    case '?':
        PacketWriteSignal(Signal);
        break;

    case 'c':
        PacketOk();
        Continue = 1;
        break;

    case 'S':
        PacketOk();
        Continue = 0;
        break;

    case 's':
        RegisterSaveArea->srr1 |= 0x400;
        PacketOk();
        Continue = 1;
        marker();
        break;

    case 'q':
        switch (DataInBuffer[1])
        {
        case 'S': /*upported => nothing*/
            PacketEmpty();
            break;

        case 'O': /*ffsets*/
            PacketEmpty();
            break;
        }
        break;

    default:
        PacketEmpty();
        break;
    }
}