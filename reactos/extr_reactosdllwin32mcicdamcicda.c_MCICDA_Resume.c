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
struct TYPE_7__ {scalar_t__ hThread; int /*<<< orphan*/  handle; int /*<<< orphan*/  dsBuf; int /*<<< orphan*/  stopEvent; } ;
typedef  TYPE_1__ WINE_MCICDAUDIO ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int /*<<< orphan*/  dwCallback; } ;
typedef  TYPE_2__* LPMCI_GENERIC_PARMS ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DSBPLAY_LOOPING ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Play (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOCTL_CDROM_RESUME_AUDIO ; 
 TYPE_1__* MCICDA_GetOpenDrv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCICDA_Notify (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int MCIERR_HARDWARE ; 
 int MCIERR_INVALID_DEVICE_ID ; 
 int MCI_NOTIFY ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD MCICDA_Resume(UINT wDevID, DWORD dwFlags, LPMCI_GENERIC_PARMS lpParms)
{
    WINE_MCICDAUDIO*	wmcda = MCICDA_GetOpenDrv(wDevID);
    DWORD               br;

    TRACE("(%04X, %08X, %p);\n", wDevID, dwFlags, lpParms);

    if (wmcda == NULL)	return MCIERR_INVALID_DEVICE_ID;

    if (wmcda->hThread != 0) {
        /* Don't restart if the playLoop thread has already stopped */
        if(WaitForSingleObject(wmcda->stopEvent, 0) != WAIT_OBJECT_0 &&
           FAILED(IDirectSoundBuffer_Play(wmcda->dsBuf, 0, 0, DSBPLAY_LOOPING)))
            return MCIERR_HARDWARE;
    }
    else if (!device_io(wmcda->handle, IOCTL_CDROM_RESUME_AUDIO, NULL, 0, NULL, 0, &br, NULL))
        return MCIERR_HARDWARE;

    if ((dwFlags & MCI_NOTIFY) && lpParms)
	MCICDA_Notify(lpParms->dwCallback, wmcda, MCI_NOTIFY_SUCCESSFUL);
    return 0;
}