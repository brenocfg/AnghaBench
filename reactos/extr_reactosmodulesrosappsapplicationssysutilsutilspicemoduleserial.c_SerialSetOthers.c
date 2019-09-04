#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int ULONG ;
typedef  int UCHAR ;

/* Variables and functions */
 int DTR ; 
 int EVEN_PARITY ; 
 scalar_t__ FCR ; 
 scalar_t__ IER ; 
 scalar_t__ LCR ; 
 scalar_t__ MCR ; 
 int NO_PARITY ; 
 int ODD_PARITY ; 
 int RTS ; 
 int inportb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outportb (int /*<<< orphan*/ ,int) ; 
 scalar_t__ usSerialPortBase ; 

void SerialSetOthers(ULONG Parity, ULONG Bits, ULONG StopBit)
{
    ULONG setting;
    UCHAR c;

    if (usSerialPortBase == 0)					return ;
    if (Bits < 5 || Bits > 8)				return ;
    if (StopBit != 1 && StopBit != 2)			return ;
    if (Parity != NO_PARITY && Parity != ODD_PARITY && Parity != EVEN_PARITY)
							return;

    setting  = Bits-5;
    setting |= ((StopBit == 1) ? 0x00 : 0x04);
    setting |= Parity;

    c = inportb((USHORT)(usSerialPortBase + LCR));
    outportb((USHORT)(usSerialPortBase + LCR), (UCHAR)(c & ~0x80)); // Reset DLAB

    // no ints
    outportb((USHORT)(usSerialPortBase + IER), (UCHAR)0);

    // clear FIFO and disable them
    outportb((USHORT)(usSerialPortBase + FCR), (UCHAR)0);

    outportb((USHORT)(usSerialPortBase + LCR), (UCHAR)setting);

    outportb((USHORT)(usSerialPortBase + MCR),  DTR | RTS);


    return ;
}