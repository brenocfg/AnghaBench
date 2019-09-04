#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UCHAR ;
struct TYPE_6__ {int dsp_version; } ;
typedef  TYPE_1__* PSOUND_BLASTER_PARAMETERS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  NotDetected ; 
 int /*<<< orphan*/  SbGetDspVersion ; 
 scalar_t__ SbReadData (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  SbWriteData (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SoundBlaster ; 
 int /*<<< orphan*/  SoundBlaster16 ; 
 int /*<<< orphan*/  SoundBlaster2 ; 
 int /*<<< orphan*/  SoundBlasterPro ; 
 int /*<<< orphan*/  WaitToRead (TYPE_1__*) ; 

ULONG
GetSoundBlasterModel(
    PSOUND_BLASTER_PARAMETERS SBDevice)
{
    UCHAR MajorVer, MinorVer;

    DPRINT("Querying DSP version\n");

    if ( ! SbWriteData(SBDevice, SbGetDspVersion) )
        return NotDetected;

    if ( ! WaitToRead(SBDevice) )
        return NotDetected;

    if ( SbReadData(SBDevice, &MajorVer) )
    {
        if ( SbReadData(SBDevice, &MinorVer) )
        {
            DPRINT("Version %d.%d\n", MajorVer, MinorVer);

            SBDevice->dsp_version = (MajorVer * 256) + MinorVer;

            if ( SBDevice->dsp_version < 0x0200 )
                return SoundBlaster;
            else if ( ( SBDevice->dsp_version & 0xFF00 ) == 0x0200 )
                return SoundBlaster2;
            else if ( ( SBDevice->dsp_version & 0xFF00 ) == 0x0300 )
                return SoundBlasterPro;
            else if ( SBDevice->dsp_version >= 0x0400 )
                return SoundBlaster16;

            return NotDetected;
        }
    }

    return NotDetected;
}