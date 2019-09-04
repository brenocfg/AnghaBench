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
typedef  int /*<<< orphan*/  capsA ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  MIXERCAPSA ;

/* Variables and functions */
 scalar_t__ MMSYSERR_BADDEVICEID ; 
 scalar_t__ mixerGetDevCapsA (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mixerGetNumDevs () ; 
 int /*<<< orphan*/  mixer_test_deviceA (scalar_t__) ; 
 int /*<<< orphan*/  mmsys_error (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void mixer_testsA(void)
{
    MIXERCAPSA capsA;
    MMRESULT rc;
    UINT ndev, d;

    trace("--- Testing ASCII functions ---\n");

    ndev=mixerGetNumDevs();
    trace("found %d Mixer devices\n",ndev);

    rc=mixerGetDevCapsA(ndev+1,&capsA,sizeof(capsA));
    ok(rc==MMSYSERR_BADDEVICEID,
       "mixerGetDevCapsA: MMSYSERR_BADDEVICEID expected, got %s\n",
       mmsys_error(rc));

    for (d=0;d<ndev;d++)
        mixer_test_deviceA(d);
}