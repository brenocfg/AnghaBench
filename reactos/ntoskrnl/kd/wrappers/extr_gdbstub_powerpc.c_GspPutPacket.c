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
typedef  int /*<<< orphan*/  VOID ;
typedef  int* PCHAR ;
typedef  size_t LONG ;
typedef  int CHAR ;

/* Variables and functions */
 char GdbGetChar () ; 
 int /*<<< orphan*/  GdbPutChar (char) ; 
 char* HexChars ; 

VOID
GspPutPacket(PCHAR Buffer)
{
    CHAR Checksum;
    LONG Count;
    CHAR ch;

    /*  $<packet info>#<Checksum>. */
    do
    {
        GdbPutChar('$');
        Checksum = 0;
        Count = 0;

        while ((ch = Buffer[Count]))
        {
            GdbPutChar(ch);
            Checksum += ch;
            Count += 1;
        }

        GdbPutChar('#');
        GdbPutChar(HexChars[(Checksum >> 4) & 0xf]);
        GdbPutChar(HexChars[Checksum & 0xf]);
    }
    while (GdbGetChar() != '+');
}