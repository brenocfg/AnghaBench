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

/* Variables and functions */
 int /*<<< orphan*/  COM1BASE ; 
 int /*<<< orphan*/  COM2BASE ; 
 int /*<<< orphan*/  COM3BASE ; 
 int /*<<< orphan*/  COM4BASE ; 
 int /*<<< orphan*/  FlushSerialBuffer () ; 
 int /*<<< orphan*/  NO_PARITY ; 
 int /*<<< orphan*/  SerialSetOthers (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SerialSetSpeed (int) ; 
 int /*<<< orphan*/  usSerialPortBase ; 

void SetupSerial(ULONG port,ULONG baudrate)
{
	USHORT ports[]={COM1BASE,COM2BASE,COM3BASE,COM4BASE};

    usSerialPortBase = ports[port-1];
	SerialSetOthers(NO_PARITY,8,1);
	SerialSetSpeed(baudrate);

    // clear out received bytes
    // else we would think there's a terminal connected
    FlushSerialBuffer();
}