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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  SB_GET_SPEAKER_STATUS ; 
 int SB_READ_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_WRITE_BYTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitToReceive (int /*<<< orphan*/ ) ; 

BOOLEAN IsSpeakerEnabled(ULONG BasePort)
{
    DPRINT("Obtaining speaker status\n");

//    if (! WaitToSend(BasePort))
//        return FALSE;

    SB_WRITE_BYTE(BasePort, SB_GET_SPEAKER_STATUS);
    if (! WaitToReceive(BasePort))
        return FALSE;

    return SB_READ_DATA(BasePort) == 0xff;
}