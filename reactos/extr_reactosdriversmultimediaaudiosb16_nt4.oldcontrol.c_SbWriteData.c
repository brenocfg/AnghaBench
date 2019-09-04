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
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PSOUND_BLASTER_PARAMETERS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SB_WRITE_DATA_PORT ; 
 int /*<<< orphan*/  SbWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WaitToWrite (int /*<<< orphan*/ ) ; 

BOOLEAN
SbWriteData(
    PSOUND_BLASTER_PARAMETERS SBDevice,
    UCHAR Data)
{
    if ( ! WaitToWrite(SBDevice) )
        return FALSE;

    DPRINT("Writing 0x%x to Sound Blaster card (data)\n", Data);
    SbWrite(SBDevice, SB_WRITE_DATA_PORT, Data);

    return TRUE;
}