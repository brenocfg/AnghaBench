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

/* Variables and functions */
 scalar_t__ ComputedCsum ; 
 scalar_t__ DataInAddr ; 
 int DataOutAddr ; 
 char* DataOutBuffer ; 
 int DataOutCsum ; 
 scalar_t__ PacketSent ; 
 scalar_t__ ParseState ; 
 int SerialRead () ; 
 int /*<<< orphan*/  SerialWrite (char) ; 
 int /*<<< orphan*/  chr (int /*<<< orphan*/ ) ; 
 char* hex ; 
 int /*<<< orphan*/  serport ; 

void PacketFinish()
{
    int i, ch, count = 0;

    PacketSent = 0;

    SerialWrite('$');
    for (i = 0; i < DataOutAddr; i++)
    {
        SerialWrite(DataOutBuffer[i]);
    }
    SerialWrite('#');
    SerialWrite(hex[(DataOutCsum >> 4) & 15]);
    SerialWrite(hex[DataOutCsum & 15]);

    while(!chr(serport) && ((ch = SerialRead()) != '+') && (ch != '$'));
    if (ch == '$')
    {
        ParseState = 0;
        DataInAddr = 0;
        ComputedCsum = 0;
    }
}