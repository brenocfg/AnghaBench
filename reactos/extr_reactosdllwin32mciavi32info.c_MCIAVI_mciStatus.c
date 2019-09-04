#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dwMicroSecPerFrame; int /*<<< orphan*/  dwTotalFrames; } ;
struct TYPE_10__ {int dwSet; int hWndPaint; int audio_stream_n; int /*<<< orphan*/  cs; scalar_t__ dwStatus; TYPE_2__ mah; TYPE_1__* inbih; scalar_t__ dwMciTimeFormat; int /*<<< orphan*/  dwCurrVideoFrame; int /*<<< orphan*/  hFile; } ;
typedef  TYPE_3__ WINE_MCIAVI ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {int dwItem; int dwReturn; int dwCallback; } ;
struct TYPE_8__ {int biBitCount; } ;
typedef  TYPE_4__* LPMCI_DGV_STATUS_PARMSW ;
typedef  int DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  HWND_32 (int) ; 
 int /*<<< orphan*/  IsIconic (int) ; 
 int /*<<< orphan*/  IsWindowVisible (int) ; 
 int /*<<< orphan*/  IsZoomed (int) ; 
 int LOWORD (int) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 void* MAKEMCIRESOURCE (scalar_t__,scalar_t__) ; 
 void* MCIAVI_ConvertFrameToTimeFormat (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 TYPE_3__* MCIAVI_mciGetOpenDev (int /*<<< orphan*/ ) ; 
 int MCIERR_INVALID_DEVICE_ID ; 
 int MCIERR_MISSING_PARAMETER ; 
 int MCIERR_NONAPPLICABLE_FUNCTION ; 
 int MCIERR_NULL_PARAMETER_BLOCK ; 
 int MCIERR_UNSUPPORTED_FUNCTION ; 
#define  MCI_DGV_STATUS_AUDIO 148 
#define  MCI_DGV_STATUS_AUDIO_STREAM 147 
#define  MCI_DGV_STATUS_BITSPERPEL 146 
#define  MCI_DGV_STATUS_FORWARD 145 
#define  MCI_DGV_STATUS_FRAME_RATE 144 
#define  MCI_DGV_STATUS_HPAL 143 
#define  MCI_DGV_STATUS_HWND 142 
#define  MCI_DGV_STATUS_PAUSE_MODE 141 
#define  MCI_DGV_STATUS_SPEED 140 
#define  MCI_DGV_STATUS_VIDEO 139 
#define  MCI_DGV_STATUS_WINDOW_MAXIMIZED 138 
#define  MCI_DGV_STATUS_WINDOW_MINIMIZED 137 
#define  MCI_DGV_STATUS_WINDOW_VISIBLE 136 
 scalar_t__ MCI_FALSE ; 
 scalar_t__ MCI_FORMAT_RETURN_BASE ; 
 scalar_t__ MCI_MODE_NOT_READY ; 
 scalar_t__ MCI_MODE_PAUSE ; 
 scalar_t__ MCI_MODE_PLAY ; 
 int MCI_NOTIFY ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 scalar_t__ MCI_OFF ; 
 scalar_t__ MCI_OFF_S ; 
 scalar_t__ MCI_ON ; 
 scalar_t__ MCI_ON_S ; 
 int MCI_RESOURCE_DRIVER ; 
 int MCI_RESOURCE_RETURNED ; 
#define  MCI_STATUS_CURRENT_TRACK 135 
 int MCI_STATUS_ITEM ; 
#define  MCI_STATUS_LENGTH 134 
#define  MCI_STATUS_MEDIA_PRESENT 133 
#define  MCI_STATUS_MODE 132 
#define  MCI_STATUS_NUMBER_OF_TRACKS 131 
#define  MCI_STATUS_POSITION 130 
#define  MCI_STATUS_READY 129 
 int MCI_STATUS_START ; 
#define  MCI_STATUS_TIME_FORMAT 128 
 int MCI_TEST ; 
 scalar_t__ MCI_TRUE ; 
 int MulDiv (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  mciDriverNotify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DWORD	MCIAVI_mciStatus(UINT wDevID, DWORD dwFlags, LPMCI_DGV_STATUS_PARMSW lpParms)
{
    WINE_MCIAVI*	wma = MCIAVI_mciGetOpenDev(wDevID);
    DWORD		ret = 0;

    if (lpParms == NULL)	return MCIERR_NULL_PARAMETER_BLOCK;
    if (wma == NULL)		return MCIERR_INVALID_DEVICE_ID;
    if (!(dwFlags & MCI_STATUS_ITEM))	return MCIERR_MISSING_PARAMETER;
    if (dwFlags & MCI_TEST)	return 0;

    EnterCriticalSection(&wma->cs);

    if (dwFlags & MCI_STATUS_ITEM) {
	switch (lpParms->dwItem) {
	case MCI_STATUS_CURRENT_TRACK:
	    lpParms->dwReturn = 1;
	    TRACE("MCI_STATUS_CURRENT_TRACK => %lu\n", lpParms->dwReturn);
	    break;
	case MCI_STATUS_LENGTH:
	    if (!wma->hFile) {
		lpParms->dwReturn = 0;
                LeaveCriticalSection(&wma->cs);
		return MCIERR_UNSUPPORTED_FUNCTION;
	    }
	    /* only one track in file is currently handled, so don't take care of MCI_TRACK flag */
	    lpParms->dwReturn = MCIAVI_ConvertFrameToTimeFormat(wma, wma->mah.dwTotalFrames, &ret);
	    TRACE("MCI_STATUS_LENGTH => %lu\n", lpParms->dwReturn);
	    break;
	case MCI_STATUS_MODE:
 	    lpParms->dwReturn = MAKEMCIRESOURCE(wma->dwStatus, wma->dwStatus);
	    ret = MCI_RESOURCE_RETURNED;
           TRACE("MCI_STATUS_MODE => 0x%04x\n", LOWORD(lpParms->dwReturn));
	    break;
	case MCI_STATUS_MEDIA_PRESENT:
	    TRACE("MCI_STATUS_MEDIA_PRESENT => TRUE\n");
	    lpParms->dwReturn = MAKEMCIRESOURCE(TRUE, MCI_TRUE);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_STATUS_NUMBER_OF_TRACKS:
	    lpParms->dwReturn = 1;
	    TRACE("MCI_STATUS_NUMBER_OF_TRACKS => %lu\n", lpParms->dwReturn);
	    break;
	case MCI_STATUS_POSITION:
	    if (!wma->hFile) {
		lpParms->dwReturn = 0;
                LeaveCriticalSection(&wma->cs);
		return MCIERR_UNSUPPORTED_FUNCTION;
	    }
	    /* only one track in file is currently handled, so don't take care of MCI_TRACK flag */
	    lpParms->dwReturn = MCIAVI_ConvertFrameToTimeFormat(wma,
							     (dwFlags & MCI_STATUS_START) ? 0 : wma->dwCurrVideoFrame,
							     &ret);
	    TRACE("MCI_STATUS_POSITION %s => %lu\n",
		  (dwFlags & MCI_STATUS_START) ? "start" : "current", lpParms->dwReturn);
	    break;
	case MCI_STATUS_READY:
	    lpParms->dwReturn = (wma->dwStatus == MCI_MODE_NOT_READY) ?
		MAKEMCIRESOURCE(FALSE, MCI_FALSE) : MAKEMCIRESOURCE(TRUE, MCI_TRUE);
	    ret = MCI_RESOURCE_RETURNED;
	    TRACE("MCI_STATUS_READY = %u\n", LOWORD(lpParms->dwReturn));
	    break;
	case MCI_STATUS_TIME_FORMAT:
	    lpParms->dwReturn = MAKEMCIRESOURCE(wma->dwMciTimeFormat,
                                wma->dwMciTimeFormat + MCI_FORMAT_RETURN_BASE);
	    TRACE("MCI_STATUS_TIME_FORMAT => %u\n", LOWORD(lpParms->dwReturn));
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_DGV_STATUS_AUDIO:
	    lpParms->dwReturn = (wma->dwSet & 3) ?
		MAKEMCIRESOURCE(MCI_ON, MCI_ON_S) : MAKEMCIRESOURCE(MCI_OFF, MCI_OFF_S);
	    ret = MCI_RESOURCE_RETURNED|MCI_RESOURCE_DRIVER;
	    TRACE("MCI_STATUS_AUDIO = %u\n", LOWORD(lpParms->dwReturn));
	    break;
	case MCI_DGV_STATUS_VIDEO:
	    lpParms->dwReturn = (wma->dwSet & 4) ?
		MAKEMCIRESOURCE(MCI_ON, MCI_ON_S) : MAKEMCIRESOURCE(MCI_OFF, MCI_OFF_S);
	    ret = MCI_RESOURCE_RETURNED|MCI_RESOURCE_DRIVER;
	    TRACE("MCI_STATUS_VIDEO = %u\n", LOWORD(lpParms->dwReturn));
	    break;

#if 0
	case MCI_AVI_STATUS_AUDIO_BREAKS:
	case MCI_AVI_STATUS_FRAMES_SKIPPED:
	case MCI_AVI_STATUS_LAST_PLAY_SPEED:
	case MCI_DGV_STATUS_AUDIO_INPUT:
	case MCI_DGV_STATUS_AUDIO_RECORD:
	case MCI_DGV_STATUS_AUDIO_SOURCE:
	case MCI_DGV_STATUS_AVGBYTESPERSEC:
	case MCI_DGV_STATUS_BASS:
	case MCI_DGV_STATUS_BITSPERSAMPLE:
	case MCI_DGV_STATUS_BLOCKALIGN:
	case MCI_DGV_STATUS_BRIGHTNESS:
	case MCI_DGV_STATUS_COLOR:
	case MCI_DGV_STATUS_CONTRAST:
	case MCI_DGV_STATUS_FILEFORMAT:
	case MCI_DGV_STATUS_FILE_MODE:
	case MCI_DGV_STATUS_FILE_COMPLETION:
	case MCI_DGV_STATUS_GAMMA:
#endif
	case MCI_DGV_STATUS_BITSPERPEL:
	    lpParms->dwReturn = wma->inbih->biBitCount;
	    TRACE("MCI_DGV_STATUS_BITSPERPEL => %lu\n", lpParms->dwReturn);
	    break;
	case MCI_DGV_STATUS_HPAL:
	    lpParms->dwReturn = 0;
	    TRACE("MCI_DGV_STATUS_HPAL => %lx\n", lpParms->dwReturn);
	    break;
	case MCI_DGV_STATUS_HWND:
           lpParms->dwReturn = (DWORD_PTR)wma->hWndPaint;
           TRACE("MCI_DGV_STATUS_HWND => %p\n", wma->hWndPaint);
	   break;
	case MCI_DGV_STATUS_WINDOW_VISIBLE:
	    lpParms->dwReturn = IsWindowVisible(wma->hWndPaint) ?
		MAKEMCIRESOURCE(TRUE, MCI_TRUE) : MAKEMCIRESOURCE(FALSE, MCI_FALSE);
	    ret = MCI_RESOURCE_RETURNED;
	    TRACE("MCI_STATUS_WINDOW_VISIBLE = %u\n", LOWORD(lpParms->dwReturn));
	    break;
	case MCI_DGV_STATUS_WINDOW_MINIMIZED:
	    lpParms->dwReturn = IsIconic(wma->hWndPaint) ?
		MAKEMCIRESOURCE(TRUE, MCI_TRUE) : MAKEMCIRESOURCE(FALSE, MCI_FALSE);
	    ret = MCI_RESOURCE_RETURNED;
	    TRACE("MCI_STATUS_WINDOW_MINIMIZED = %u\n", LOWORD(lpParms->dwReturn));
	    break;
	case MCI_DGV_STATUS_WINDOW_MAXIMIZED:
	    lpParms->dwReturn = IsZoomed(wma->hWndPaint) ?
		MAKEMCIRESOURCE(TRUE, MCI_TRUE) : MAKEMCIRESOURCE(FALSE, MCI_FALSE);
	    ret = MCI_RESOURCE_RETURNED;
	    TRACE("MCI_STATUS_WINDOW_MMAXIMIZED = %u\n", LOWORD(lpParms->dwReturn));
	    break;
	case MCI_DGV_STATUS_SPEED:
	    lpParms->dwReturn = 1000;
	    TRACE("MCI_DGV_STATUS_SPEED = %lu\n", lpParms->dwReturn);
	    break;
	case MCI_DGV_STATUS_FRAME_RATE:
	    /* FIXME: 1000 is a settable speed multiplier */
	    lpParms->dwReturn = MulDiv(1000000,1000,wma->mah.dwMicroSecPerFrame);
	    TRACE("MCI_DGV_STATUS_FRAME_RATE = %lu\n", lpParms->dwReturn);
	    break;
	case MCI_DGV_STATUS_FORWARD:
	    lpParms->dwReturn = MAKEMCIRESOURCE(TRUE, MCI_TRUE);
	    ret = MCI_RESOURCE_RETURNED;
	    TRACE("MCI_DGV_STATUS_FORWARD = %u\n", LOWORD(lpParms->dwReturn));
	    break;
	case MCI_DGV_STATUS_PAUSE_MODE:
	    if (wma->dwStatus != MCI_MODE_PAUSE) {
		LeaveCriticalSection(&wma->cs);
		return MCIERR_NONAPPLICABLE_FUNCTION;
	    }
	    lpParms->dwReturn = MAKEMCIRESOURCE(MCI_MODE_PLAY, MCI_MODE_PLAY);
	    ret = MCI_RESOURCE_RETURNED;
	    TRACE("MCI_STATUS_MODE => 0x%04x\n", LOWORD(lpParms->dwReturn));
	    break;
	case MCI_DGV_STATUS_AUDIO_STREAM:
	   lpParms->dwReturn = wma->audio_stream_n;
	   TRACE("MCI_DGV_STATUS_AUDIO_STREAM => %lu\n", lpParms->dwReturn);
	   break;
#if 0
	case MCI_DGV_STATUS_KEY_COLOR:
	case MCI_DGV_STATUS_KEY_INDEX:
	case MCI_DGV_STATUS_MONITOR:
	case MCI_DGV_MONITOR_FILE:
	case MCI_DGV_MONITOR_INPUT:
	case MCI_DGV_STATUS_MONITOR_METHOD:
	case MCI_DGV_STATUS_SAMPLESPERSECOND:
	case MCI_DGV_STATUS_SEEK_EXACTLY:
	case MCI_DGV_STATUS_SHARPNESS:
	case MCI_DGV_STATUS_SIZE:
	case MCI_DGV_STATUS_SMPTE:
	case MCI_DGV_STATUS_STILL_FILEFORMAT:
	case MCI_DGV_STATUS_TINT:
	case MCI_DGV_STATUS_TREBLE:
	case MCI_DGV_STATUS_UNSAVED:
	case MCI_DGV_STATUS_VIDEO_RECORD:
	case MCI_DGV_STATUS_VIDEO_SOURCE:
	case MCI_DGV_STATUS_VIDEO_SRC_NUM:
	case MCI_DGV_STATUS_VIDEO_STREAM:
	case MCI_DGV_STATUS_VOLUME:
#endif
	default:
            FIXME("Unknown command %08X !\n", lpParms->dwItem);
            TRACE("(%04x, %08X, %p)\n", wDevID, dwFlags, lpParms);
            LeaveCriticalSection(&wma->cs);
	    return MCIERR_UNSUPPORTED_FUNCTION;
	}
    }

    if (dwFlags & MCI_NOTIFY) {
	TRACE("MCI_NOTIFY_SUCCESSFUL %08lX !\n", lpParms->dwCallback);
	mciDriverNotify(HWND_32(LOWORD(lpParms->dwCallback)),
                       wDevID, MCI_NOTIFY_SUCCESSFUL);
    }
    LeaveCriticalSection(&wma->cs);
    return ret;
}