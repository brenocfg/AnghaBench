#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  capsW ;
typedef  int /*<<< orphan*/  capsA ;
typedef  int /*<<< orphan*/  WAVEINCAPSW ;
typedef  int /*<<< orphan*/  WAVEINCAPSA ;
struct TYPE_3__ {int nChannels; int wBitsPerSample; int nSamplesPerSec; int nBlockAlign; int nAvgBytesPerSec; scalar_t__ cbSize; int /*<<< orphan*/  wFormatTag; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
typedef  int UINT ;
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  HWAVEIN ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_NULL ; 
 int /*<<< orphan*/  DRVM_MAPPER_PREFERRED_GET ; 
 scalar_t__ MMSYSERR_BADDEVICEID ; 
 scalar_t__ MMSYSERR_NODRIVER ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int WAVE_MAPPER ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  dev_name (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  trace (char*,int) ; 
 scalar_t__ waveInGetDevCapsA (int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ waveInGetDevCapsW (int,int /*<<< orphan*/ *,int) ; 
 int waveInGetNumDevs () ; 
 scalar_t__ waveInMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waveInOpen (int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wave_in_error (scalar_t__) ; 
 int /*<<< orphan*/  wave_in_test_device (int) ; 

__attribute__((used)) static void wave_in_tests(void)
{
    WAVEINCAPSA capsA;
    WAVEINCAPSW capsW;
    WAVEFORMATEX format;
    HWAVEIN win;
    MMRESULT rc;
    DWORD preferred, status;
    UINT ndev,d;

    ndev=waveInGetNumDevs();
    trace("found %d WaveIn devices\n",ndev);

    rc = waveInMessage((HWAVEIN)WAVE_MAPPER, DRVM_MAPPER_PREFERRED_GET,
            (DWORD_PTR)&preferred, (DWORD_PTR)&status);
    ok((ndev == 0 && (rc == MMSYSERR_NODRIVER || rc == MMSYSERR_BADDEVICEID)) ||
            rc == MMSYSERR_NOTSUPPORTED ||
            rc == MMSYSERR_NOERROR, "waveInMessage(DRVM_MAPPER_PREFERRED_GET) failed: %u\n", rc);

    if(rc != MMSYSERR_NOTSUPPORTED)
        ok((ndev == 0 && (preferred == -1 || broken(preferred != -1))) ||
                preferred < ndev, "Got invalid preferred device: 0x%x\n", preferred);

    rc=waveInGetDevCapsA(ndev+1,&capsA,sizeof(capsA));
    ok(rc==MMSYSERR_BADDEVICEID,
       "waveInGetDevCapsA(%s): MMSYSERR_BADDEVICEID expected, got %s\n",
       dev_name(ndev+1),wave_in_error(rc));

    rc=waveInGetDevCapsA(WAVE_MAPPER,&capsA,sizeof(capsA));
    ok(rc==MMSYSERR_NOERROR || rc==MMSYSERR_NODRIVER || (!ndev && (rc==MMSYSERR_BADDEVICEID)),
       "waveInGetDevCapsA(%s): got %s\n",dev_name(WAVE_MAPPER),wave_in_error(rc));

    rc=waveInGetDevCapsW(ndev+1,&capsW,sizeof(capsW));
    ok(rc==MMSYSERR_BADDEVICEID || rc==MMSYSERR_NOTSUPPORTED,
       "waveInGetDevCapsW(%s): MMSYSERR_BADDEVICEID or MMSYSERR_NOTSUPPORTED "
       "expected, got %s\n",dev_name(ndev+1),wave_in_error(rc));

    rc=waveInGetDevCapsW(WAVE_MAPPER,&capsW,sizeof(capsW));
    ok(rc==MMSYSERR_NOERROR || rc==MMSYSERR_NODRIVER ||
       rc==MMSYSERR_NOTSUPPORTED || (!ndev && (rc==MMSYSERR_BADDEVICEID)),
       "waveInGetDevCapsW(%s): got %s\n", dev_name(ndev+1),wave_in_error(rc));

    format.wFormatTag=WAVE_FORMAT_PCM;
    format.nChannels=2;
    format.wBitsPerSample=16;
    format.nSamplesPerSec=44100;
    format.nBlockAlign=format.nChannels*format.wBitsPerSample/8;
    format.nAvgBytesPerSec=format.nSamplesPerSec*format.nBlockAlign;
    format.cbSize=0;
    rc=waveInOpen(&win,ndev+1,&format,0,0,CALLBACK_NULL);
    ok(rc==MMSYSERR_BADDEVICEID,
       "waveInOpen(%s): MMSYSERR_BADDEVICEID expected, got %s\n",
       dev_name(ndev+1),wave_in_error(rc));

    for (d=0;d<ndev;d++)
        wave_in_test_device(d);

    if (ndev>0)
        wave_in_test_device(WAVE_MAPPER);
}