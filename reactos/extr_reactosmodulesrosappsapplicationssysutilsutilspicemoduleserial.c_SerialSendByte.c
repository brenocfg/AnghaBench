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
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ LSR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TXR ; 
 int XMTRDY ; 
 int inportb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outportb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usSerialPortBase ; 

BOOLEAN SerialSendByte(UCHAR x)
{
    ULONG timeout;

    timeout = 0x00FFFFL;

    // Wait for transmitter to clear
    while ((inportb((USHORT)(usSerialPortBase + LSR)) & XMTRDY) == 0)
        if (!(--timeout))
        {
			return FALSE;
        }

    outportb((USHORT)(usSerialPortBase + TXR), x);

	return TRUE;
}