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
struct TYPE_7__ {scalar_t__ dwStatus; } ;
typedef  TYPE_1__ WINE_MCIWAVE ;
struct TYPE_8__ {int /*<<< orphan*/  dwCallback; } ;
typedef  int /*<<< orphan*/  MCIDEVICEID ;
typedef  TYPE_2__* LPMCI_GENERIC_PARMS ;
typedef  int DWORD ;

/* Variables and functions */
 int MCIERR_INVALID_DEVICE_ID ; 
 int MCIERR_NONAPPLICABLE_FUNCTION ; 
 scalar_t__ MCI_MODE_STOP ; 
 int MCI_NOTIFY ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 int MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 TYPE_1__* WAVE_mciGetOpenDev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAVE_mciNotify (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD WAVE_mciCue(MCIDEVICEID wDevID, DWORD dwFlags, LPMCI_GENERIC_PARMS lpParms)
{
    WINE_MCIWAVE*	wmw = WAVE_mciGetOpenDev(wDevID);

    TRACE("(%u, %08X, %p);\n", wDevID, dwFlags, lpParms);

    /* Tests on systems without sound drivers show that Cue, like
     * Record and Play, opens winmm, returning MCIERR_WAVE_xyPUTSUNSUITABLE.
     * The first Cue Notify does not immediately return the
     * notification, as if a player or recorder thread is started.
     * PAUSE mode is reported when successful, but this mode is
     * different from the normal Pause, because a) Pause then returns
     * NONAPPLICABLE_FUNCTION instead of 0 and b) Set Channels etc. is
     * still accepted, returning the original notification as ABORTED.
     * I.e. Cue allows subsequent format changes, unlike Record or
     * Open file, closes winmm if the format changes and stops this
     * thread.
     * Wine creates one player or recorder thread per async. Play or
     * Record command.  Notification behaviour suggests that MS-W*
     * reuses a single thread to improve response times.  Having Cue
     * start this thread early helps to improve Play/Record's initial
     * response time.  In effect, Cue is a performance hint, which
     * justifies our almost no-op implementation.
     */

    if (wmw == NULL)		return MCIERR_INVALID_DEVICE_ID;
    if (wmw->dwStatus != MCI_MODE_STOP) return MCIERR_NONAPPLICABLE_FUNCTION;

    if ((dwFlags & MCI_NOTIFY) && lpParms)
	WAVE_mciNotify(lpParms->dwCallback,wmw,MCI_NOTIFY_SUCCESSFUL);

    return MMSYSERR_NOERROR;
}