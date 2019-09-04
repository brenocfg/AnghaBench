#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dwStatus; int /*<<< orphan*/  hWave; int /*<<< orphan*/  fInput; int /*<<< orphan*/  hCallback; } ;
typedef  TYPE_1__ WINE_MCIWAVE ;
struct TYPE_8__ {int /*<<< orphan*/  dwCallback; } ;
typedef  int /*<<< orphan*/  MCIDEVICEID ;
typedef  TYPE_2__* LPMCI_GENERIC_PARMS ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ InterlockedExchangePointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MCIERR_INVALID_DEVICE_ID ; 
 int MCI_MODE_NOT_READY ; 
#define  MCI_MODE_PAUSE 130 
#define  MCI_MODE_PLAY 129 
#define  MCI_MODE_RECORD 128 
 int MCI_MODE_STOP ; 
 scalar_t__ MCI_NOTIFY ; 
 int /*<<< orphan*/  MCI_NOTIFY_ABORTED ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__,TYPE_2__*) ; 
 TYPE_1__* WAVE_mciGetOpenDev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAVE_mciNotify (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mciDriverNotify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waveInReset (int /*<<< orphan*/ ) ; 
 scalar_t__ waveOutReset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD WAVE_mciStop(MCIDEVICEID wDevID, DWORD dwFlags, LPMCI_GENERIC_PARMS lpParms)
{
    DWORD 		dwRet = 0;
    WINE_MCIWAVE*	wmw = WAVE_mciGetOpenDev(wDevID);

    TRACE("(%u, %08X, %p);\n", wDevID, dwFlags, lpParms);

    if (wmw == NULL)		return MCIERR_INVALID_DEVICE_ID;

    if (wmw->dwStatus != MCI_MODE_STOP) {
	HANDLE old = InterlockedExchangePointer(&wmw->hCallback, NULL);
	if (old) mciDriverNotify(old, wDevID, MCI_NOTIFY_ABORTED);
    }

    /* wait for playback thread (if any) to exit before processing further */
    switch (wmw->dwStatus) {
    case MCI_MODE_PAUSE:
    case MCI_MODE_PLAY:
    case MCI_MODE_RECORD:
	{
	    int oldStat = wmw->dwStatus;
	    wmw->dwStatus = MCI_MODE_NOT_READY;
	    if (oldStat == MCI_MODE_PAUSE)
		dwRet = (wmw->fInput) ? waveInReset(wmw->hWave) : waveOutReset(wmw->hWave);
	}
	while (wmw->dwStatus != MCI_MODE_STOP)
	    Sleep(10);
	break;
    }

    /* sanity resets */
    wmw->dwStatus = MCI_MODE_STOP;

    if ((dwFlags & MCI_NOTIFY) && lpParms && MMSYSERR_NOERROR==dwRet)
	WAVE_mciNotify(lpParms->dwCallback, wmw, MCI_NOTIFY_SUCCESSFUL);

    return dwRet;
}