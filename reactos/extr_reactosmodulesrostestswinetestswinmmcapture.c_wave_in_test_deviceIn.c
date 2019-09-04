#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mmt ;
typedef  int /*<<< orphan*/  frag ;
typedef  scalar_t__ WORD ;
struct TYPE_19__ {int dwFormats; } ;
typedef  TYPE_2__ WAVEINCAPSA ;
struct TYPE_20__ {scalar_t__ dwBufferLength; scalar_t__ dwBytesRecorded; int dwFlags; int /*<<< orphan*/  lpData; scalar_t__ lpNext; scalar_t__ dwLoops; scalar_t__ dwUser; } ;
typedef  TYPE_3__ WAVEHDR ;
struct TYPE_21__ {scalar_t__ nChannels; scalar_t__ wBitsPerSample; int nSamplesPerSec; scalar_t__ nAvgBytesPerSec; int /*<<< orphan*/  wFormatTag; } ;
typedef  TYPE_4__ WAVEFORMATEX ;
struct TYPE_18__ {scalar_t__ cb; } ;
struct TYPE_22__ {scalar_t__ wType; TYPE_1__ u; } ;
typedef  TYPE_5__ MMTIME ;
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  HWAVEOUT ;
typedef  int /*<<< orphan*/ * HWAVEIN ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int CALLBACK_EVENT ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INFINITE ; 
 scalar_t__ MMSYSERR_ALLOCATED ; 
 scalar_t__ MMSYSERR_BADDEVICEID ; 
 scalar_t__ MMSYSERR_INVALFLAG ; 
 scalar_t__ MMSYSERR_NODRIVER ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ MMSYSERR_NOTENABLED ; 
 scalar_t__ MMSYSERR_NOTSUPPORTED ; 
 scalar_t__ TIME_BYTES ; 
 int WAIT_OBJECT_0 ; 
 scalar_t__ WAVERR_BADFORMAT ; 
 int WAVE_FORMAT_DIRECT ; 
 int WAVE_MAPPED ; 
 int /*<<< orphan*/  WAVE_MAPPER ; 
 int WHDR_DONE ; 
 int WHDR_PREPARED ; 
 int WaitForSingleObject (scalar_t__,int) ; 
 int /*<<< orphan*/  check_position (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ dev_name (int) ; 
 int /*<<< orphan*/  get_format_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmsys_error (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,...) ; 
 scalar_t__ waveInAddBuffer (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ waveInClose (int /*<<< orphan*/ *) ; 
 scalar_t__ waveInGetPosition (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 scalar_t__ waveInOpen (int /*<<< orphan*/ **,int,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ waveInPrepareHeader (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ waveInStart (int /*<<< orphan*/ *) ; 
 scalar_t__ waveInStop (int /*<<< orphan*/ *) ; 
 scalar_t__ waveInUnprepareHeader (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ waveOutClose (int /*<<< orphan*/ ) ; 
 scalar_t__ waveOutOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ waveOutPrepareHeader (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ waveOutUnprepareHeader (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ waveOutWrite (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ wave_in_error (scalar_t__) ; 
 int /*<<< orphan*/  wave_open_flags (int) ; 
 scalar_t__ wave_out_error (scalar_t__) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void wave_in_test_deviceIn(int device, WAVEFORMATEX *pwfx, DWORD format, DWORD flags,
        WAVEINCAPSA *pcaps)
{
    HWAVEIN win;
    HANDLE hevent = CreateEventW(NULL, FALSE, FALSE, NULL);
    WAVEHDR frag;
    MMRESULT rc;
    DWORD res;
    MMTIME mmt;
    WORD nChannels = pwfx->nChannels;
    WORD wBitsPerSample = pwfx->wBitsPerSample;
    DWORD nSamplesPerSec = pwfx->nSamplesPerSec;

    win=NULL;
    rc=waveInOpen(&win,device,pwfx,(DWORD_PTR)hevent,0,CALLBACK_EVENT|flags);
    /* Note: Win9x doesn't know WAVE_FORMAT_DIRECT */
    ok(rc==MMSYSERR_NOERROR || rc==MMSYSERR_BADDEVICEID ||
       rc==MMSYSERR_NOTENABLED || rc==MMSYSERR_NODRIVER ||
       rc==MMSYSERR_ALLOCATED ||
       ((rc==WAVERR_BADFORMAT || rc==MMSYSERR_NOTSUPPORTED) &&
       (flags & WAVE_FORMAT_DIRECT) && !(pcaps->dwFormats & format)) ||
       ((rc==WAVERR_BADFORMAT || rc==MMSYSERR_NOTSUPPORTED) &&
       (!(flags & WAVE_FORMAT_DIRECT) || (flags & WAVE_MAPPED)) &&
       !(pcaps->dwFormats & format)) ||
       (rc==MMSYSERR_INVALFLAG && (flags & WAVE_FORMAT_DIRECT)),
       "waveInOpen(%s): format=%dx%2dx%d flags=%x(%s) rc=%s\n",
       dev_name(device),pwfx->nSamplesPerSec,pwfx->wBitsPerSample,
       pwfx->nChannels,CALLBACK_EVENT|flags,
       wave_open_flags(CALLBACK_EVENT|flags),wave_in_error(rc));
    if ((rc==WAVERR_BADFORMAT || rc==MMSYSERR_NOTSUPPORTED) &&
       (flags & WAVE_FORMAT_DIRECT) && (pcaps->dwFormats & format))
        trace(" Reason: The device lists this format as supported in its "
              "capabilities but opening it failed.\n");
    if ((rc==WAVERR_BADFORMAT || rc==MMSYSERR_NOTSUPPORTED) &&
       !(pcaps->dwFormats & format))
        trace("waveInOpen(%s): format=%dx%2dx%d %s rc=%s failed but format "
              "not supported so OK.\n",dev_name(device),pwfx->nSamplesPerSec,
              pwfx->wBitsPerSample,pwfx->nChannels,
              flags & WAVE_FORMAT_DIRECT ? "flags=WAVE_FORMAT_DIRECT" :
              flags & WAVE_MAPPED ? "flags=WAVE_MAPPED" : "", mmsys_error(rc));
    if (rc!=MMSYSERR_NOERROR) {
        CloseHandle(hevent);
        return;
    }
    res=WaitForSingleObject(hevent,1000);
    ok(res==WAIT_OBJECT_0,"WaitForSingleObject failed for open\n");

    ok(pwfx->nChannels==nChannels &&
       pwfx->wBitsPerSample==wBitsPerSample &&
       pwfx->nSamplesPerSec==nSamplesPerSec,
       "got the wrong format: %dx%2dx%d instead of %dx%2dx%d\n",
       pwfx->nSamplesPerSec, pwfx->wBitsPerSample,
       pwfx->nChannels, nSamplesPerSec, wBitsPerSample, nChannels);

    /* Check that the position is 0 at start */
    check_position(device, win, 0, pwfx);

    frag.lpData=HeapAlloc(GetProcessHeap(), 0, pwfx->nAvgBytesPerSec);
    frag.dwBufferLength=pwfx->nAvgBytesPerSec;
    frag.dwBytesRecorded=0;
    frag.dwUser=0;
    frag.dwFlags=0;
    frag.dwLoops=0;
    frag.lpNext=0;

    rc=waveInPrepareHeader(win, &frag, sizeof(frag));
    ok(rc==MMSYSERR_NOERROR, "waveInPrepareHeader(%s): rc=%s\n",
       dev_name(device),wave_in_error(rc));
    ok(frag.dwFlags&WHDR_PREPARED,"waveInPrepareHeader(%s): prepared flag "
       "not set\n",dev_name(device));

    if (winetest_interactive && rc==MMSYSERR_NOERROR) {
        trace("Recording for 1 second at %5dx%2dx%d %s %s\n",
              pwfx->nSamplesPerSec, pwfx->wBitsPerSample,pwfx->nChannels,
              get_format_str(pwfx->wFormatTag),
              flags & WAVE_FORMAT_DIRECT ? "WAVE_FORMAT_DIRECT" :
              flags & WAVE_MAPPED ? "WAVE_MAPPED" : "");
        rc=waveInAddBuffer(win, &frag, sizeof(frag));
        ok(rc==MMSYSERR_NOERROR,"waveInAddBuffer(%s): rc=%s\n",
           dev_name(device),wave_in_error(rc));

        /* Check that the position is 0 at start */
        check_position(device, win, 0, pwfx);

        rc=waveInStart(win);
        ok(rc==MMSYSERR_NOERROR,"waveInStart(%s): rc=%s\n",
           dev_name(device),wave_in_error(rc));

        res = WaitForSingleObject(hevent,1200);
        ok(res==WAIT_OBJECT_0,"WaitForSingleObject failed for header\n");
        ok(frag.dwFlags&WHDR_DONE,"WHDR_DONE not set in frag.dwFlags\n");
        ok(frag.dwBytesRecorded==pwfx->nAvgBytesPerSec,
           "frag.dwBytesRecorded=%d, should=%d\n",
           frag.dwBytesRecorded,pwfx->nAvgBytesPerSec);

        mmt.wType = TIME_BYTES;
        rc=waveInGetPosition(win, &mmt, sizeof(mmt));
        ok(rc==MMSYSERR_NOERROR,"waveInGetPosition(%s): rc=%s\n",
           dev_name(device),wave_in_error(rc));
        ok(mmt.wType == TIME_BYTES, "doesn't support TIME_BYTES: %u\n", mmt.wType);
        ok(mmt.u.cb == frag.dwBytesRecorded, "Got wrong position: %u\n", mmt.u.cb);

        /* stop playing on error */
        if (res!=WAIT_OBJECT_0) {
            rc=waveInStop(win);
            ok(rc==MMSYSERR_NOERROR,
               "waveInStop(%s): rc=%s\n",dev_name(device),wave_in_error(rc));
        }
    }

    rc=waveInUnprepareHeader(win, &frag, sizeof(frag));
    ok(rc==MMSYSERR_NOERROR,"waveInUnprepareHeader(%s): rc=%s\n",
       dev_name(device),wave_in_error(rc));

    rc=waveInClose(win);
    ok(rc==MMSYSERR_NOERROR,
       "waveInClose(%s): rc=%s\n",dev_name(device),wave_in_error(rc));
    res=WaitForSingleObject(hevent,1000);
    ok(res==WAIT_OBJECT_0,"WaitForSingleObject failed for close\n");

    if (winetest_interactive)
    {
        /*
         * Now play back what we recorded
         */
        HWAVEOUT wout;

        trace("Playing back recorded sound\n");
        rc=waveOutOpen(&wout,WAVE_MAPPER,pwfx,(DWORD_PTR)hevent,0,CALLBACK_EVENT);
        ok(rc==MMSYSERR_NOERROR || rc==MMSYSERR_BADDEVICEID ||
           rc==MMSYSERR_NOTENABLED || rc==MMSYSERR_NODRIVER ||
           rc==MMSYSERR_ALLOCATED ||
           ((rc==WAVERR_BADFORMAT || rc==MMSYSERR_NOTSUPPORTED) &&
            !(pcaps->dwFormats & format)),
           "waveOutOpen(%s) format=%dx%2dx%d flags=%x(%s) rc=%s\n",
           dev_name(device),pwfx->nSamplesPerSec,pwfx->wBitsPerSample,
           pwfx->nChannels,CALLBACK_EVENT|flags,
           wave_open_flags(CALLBACK_EVENT),wave_out_error(rc));
        if (rc==MMSYSERR_NOERROR)
        {
            rc=waveOutPrepareHeader(wout, &frag, sizeof(frag));
            ok(rc==MMSYSERR_NOERROR,"waveOutPrepareHeader(%s): rc=%s\n",
               dev_name(device),wave_out_error(rc));

            if (rc==MMSYSERR_NOERROR)
            {
                WaitForSingleObject(hevent,INFINITE);
                rc=waveOutWrite(wout, &frag, sizeof(frag));
                ok(rc==MMSYSERR_NOERROR,"waveOutWrite(%s): rc=%s\n",
                   dev_name(device),wave_out_error(rc));
                WaitForSingleObject(hevent,INFINITE);

                rc=waveOutUnprepareHeader(wout, &frag, sizeof(frag));
                ok(rc==MMSYSERR_NOERROR,"waveOutUnprepareHeader(%s): rc=%s\n",
                   dev_name(device),wave_out_error(rc));
            }
            rc=waveOutClose(wout);
            ok(rc==MMSYSERR_NOERROR,"waveOutClose(%s): rc=%s\n",
               dev_name(device),wave_out_error(rc));
        }
        else
            trace("Unable to play back the recorded sound\n");
    }

    HeapFree(GetProcessHeap(), 0, frag.lpData);
    CloseHandle(hevent);
}