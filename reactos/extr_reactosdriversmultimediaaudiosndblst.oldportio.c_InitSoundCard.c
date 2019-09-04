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
typedef  int USHORT ;
typedef  int ULONG ;
typedef  int UCHAR ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int FALSE ; 
 scalar_t__ SB_DSP_READY ; 
 int /*<<< orphan*/  SB_GET_DSP_VERSION ; 
 scalar_t__ SB_READ_DATA (int) ; 
 int SB_TIMEOUT ; 
 int /*<<< orphan*/  SB_WRITE_DATA (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_WRITE_RESET (int,int) ; 
 scalar_t__ WaitToReceive (int) ; 
 int /*<<< orphan*/  WaitToSend (int) ; 

USHORT InitSoundCard(ULONG BasePort)
{
    ULONG TimeOut;
    BOOLEAN Status;
    UCHAR DSP_Major, DSP_Minor;

    DPRINT("InitSoundCard() called\n");

    DPRINT("Resetting sound card\n");
//    if (!WaitToSend(BasePort))
//        return FALSE;

    SB_WRITE_RESET(BasePort, 0x01);
    for (TimeOut = 0; TimeOut < 30000; TimeOut ++); // Wait a while
    SB_WRITE_RESET(BasePort, 0x00);

    // Check if it's OK to receive (some cards will ignore the above reset
    // command and so will not issue an ACK, so time out is NOT an error)
    DPRINT("Waiting for an ACK\n");
    if (WaitToReceive(BasePort))
    {
        // Check to make sure the reset was acknowledged:
        for (TimeOut = SB_TIMEOUT;
             (Status = (SB_READ_DATA(BasePort) != SB_DSP_READY) && (TimeOut > 0));
             TimeOut --);
    }

    DPRINT("Querying DSP version\n");
    if (! WaitToSend(BasePort))
        return FALSE;

    SB_WRITE_DATA(BasePort, SB_GET_DSP_VERSION);

    if (! WaitToReceive(BasePort))
        return FALSE;

    DSP_Major = SB_READ_DATA(BasePort);
    DSP_Minor = SB_READ_DATA(BasePort);

    DPRINT("DSP v%d.%d\n", DSP_Major, DSP_Minor);

    // if audio is disabled,
    // version tests return 0xFF everywhere
    if (DSP_Major == 0xFF && DSP_Minor == 0xFF)
        return FALSE;

    DPRINT("Sound card initialized!\n");

    return (DSP_Major * 256) + DSP_Minor;
}