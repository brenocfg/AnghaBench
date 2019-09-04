#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fmt ;
typedef  int /*<<< orphan*/  data ;
typedef  int WORD ;
struct TYPE_21__ {int dwTimeFormat; int /*<<< orphan*/  handle; } ;
typedef  TYPE_3__ WINE_MCICDAUDIO ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_25__ {void* Format; } ;
struct TYPE_24__ {size_t FirstTrack; size_t LastTrack; TYPE_1__* TrackData; } ;
struct TYPE_23__ {int dwItem; int dwReturn; size_t dwTrack; int /*<<< orphan*/  dwCallback; } ;
struct TYPE_20__ {int TrackNumber; int /*<<< orphan*/  AbsoluteAddress; } ;
struct TYPE_22__ {TYPE_2__ CurrentPosition; } ;
struct TYPE_19__ {int Control; } ;
typedef  TYPE_4__ SUB_Q_CHANNEL_DATA ;
typedef  TYPE_5__* LPMCI_STATUS_PARMS ;
typedef  int DWORD ;
typedef  TYPE_6__ CDROM_TOC ;
typedef  TYPE_7__ CDROM_SUB_Q_DATA_FORMAT ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int FRAME_OF_ADDR (int /*<<< orphan*/ ) ; 
 void* FRAME_OF_TOC (TYPE_6__,size_t) ; 
 scalar_t__ HRESULT_CODE (int) ; 
 void* IOCTL_CDROM_CURRENT_POSITION ; 
 int /*<<< orphan*/  IOCTL_CDROM_READ_Q_CHANNEL ; 
 int /*<<< orphan*/  LOWORD (int) ; 
 void* MAKEMCIRESOURCE (int,int) ; 
 void* MCICDA_CalcTime (TYPE_3__*,int,int,int*) ; 
 int MCICDA_GetError (TYPE_3__*) ; 
 TYPE_3__* MCICDA_GetOpenDrv (int /*<<< orphan*/ ) ; 
 int MCICDA_GetStatus (TYPE_3__*) ; 
 int /*<<< orphan*/  MCICDA_Notify (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCICDA_ReadTOC (TYPE_3__*,TYPE_6__*,int*) ; 
 int MCIERR_FLAGS_NOT_COMPATIBLE ; 
 int MCIERR_INVALID_DEVICE_ID ; 
 int MCIERR_MISSING_PARAMETER ; 
 int MCIERR_NULL_PARAMETER_BLOCK ; 
 int MCIERR_OUTOFRANGE ; 
 int MCIERR_UNSUPPORTED_FUNCTION ; 
#define  MCI_CDA_STATUS_TYPE_TRACK 140 
 int MCI_CDA_TRACK_AUDIO ; 
 int MCI_CDA_TRACK_OTHER ; 
 int MCI_FALSE ; 
 int MCI_FORMAT_MSF ; 
 int MCI_FORMAT_RETURN_BASE ; 
 int MCI_FORMAT_TMSF ; 
#define  MCI_MODE_NOT_READY 139 
#define  MCI_MODE_OPEN 138 
 int MCI_NOTIFY ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 int MCI_RESOURCE_RETURNED ; 
#define  MCI_STATUS_CURRENT_TRACK 137 
 int MCI_STATUS_ITEM ; 
#define  MCI_STATUS_LENGTH 136 
#define  MCI_STATUS_MEDIA_PRESENT 135 
#define  MCI_STATUS_MODE 134 
#define  MCI_STATUS_NUMBER_OF_TRACKS 133 
#define  MCI_STATUS_POSITION 132 
#define  MCI_STATUS_READY 131 
#define  MCI_STATUS_START 130 
#define  MCI_STATUS_TIME_FORMAT 129 
#define  MCI_TRACK 128 
 int MCI_TRUE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int TRUE ; 
 int /*<<< orphan*/  device_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int,TYPE_4__*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD MCICDA_Status(UINT wDevID, DWORD dwFlags, LPMCI_STATUS_PARMS lpParms)
{
    WINE_MCICDAUDIO*	        wmcda = MCICDA_GetOpenDrv(wDevID);
    DWORD	                ret = 0;
    CDROM_SUB_Q_DATA_FORMAT     fmt;
    SUB_Q_CHANNEL_DATA          data;
    CDROM_TOC                   toc;
    DWORD                       br;

    TRACE("(%04X, %08X, %p);\n", wDevID, dwFlags, lpParms);

    if (lpParms == NULL) return MCIERR_NULL_PARAMETER_BLOCK;
    if (wmcda == NULL) return MCIERR_INVALID_DEVICE_ID;

    if (dwFlags & MCI_STATUS_ITEM) {
	TRACE("dwItem = %x\n", lpParms->dwItem);
	switch (lpParms->dwItem) {
	case MCI_STATUS_CURRENT_TRACK:
            fmt.Format = IOCTL_CDROM_CURRENT_POSITION;
            if (!device_io(wmcda->handle, IOCTL_CDROM_READ_Q_CHANNEL, &fmt, sizeof(fmt),
                                 &data, sizeof(data), &br, NULL))
            {
		return MCICDA_GetError(wmcda);
		/* alt. data.CurrentPosition.TrackNumber = 1; -- what native yields */
	    }
	    lpParms->dwReturn = data.CurrentPosition.TrackNumber;
            TRACE("CURRENT_TRACK=%lu\n", lpParms->dwReturn);
	    break;
	case MCI_STATUS_LENGTH:
	    if (!MCICDA_ReadTOC(wmcda, &toc, &br))
                return MCICDA_GetError(wmcda);

	    if (dwFlags & MCI_TRACK) {
		TRACE("MCI_TRACK #%u LENGTH=??? !\n", lpParms->dwTrack);
		if (lpParms->dwTrack < toc.FirstTrack || lpParms->dwTrack > toc.LastTrack)
		    return MCIERR_OUTOFRANGE;
		lpParms->dwReturn = FRAME_OF_TOC(toc, lpParms->dwTrack + 1) -
                    FRAME_OF_TOC(toc, lpParms->dwTrack);
		/* Windows returns one frame less than the total track length for the
		   last track on the CD.  See CDDB HOWTO.  Verified on Win95OSR2. */
		if (lpParms->dwTrack == toc.LastTrack)
		    lpParms->dwReturn--;
	    } else {
		/* Sum of the lengths of all of the tracks.  Inherits the
		   'off by one frame' behavior from the length of the last track.
		   See above comment. */
		lpParms->dwReturn = FRAME_OF_TOC(toc, toc.LastTrack + 1) -
                    FRAME_OF_TOC(toc, toc.FirstTrack) - 1;
	    }
	    lpParms->dwReturn = MCICDA_CalcTime(wmcda,
						 (wmcda->dwTimeFormat == MCI_FORMAT_TMSF)
						    ? MCI_FORMAT_MSF : wmcda->dwTimeFormat,
						 lpParms->dwReturn,
						 &ret);
            TRACE("LENGTH=%lu\n", lpParms->dwReturn);
	    break;
	case MCI_STATUS_MODE:
            lpParms->dwReturn = MCICDA_GetStatus(wmcda);
            TRACE("MCI_STATUS_MODE=%08lX\n", lpParms->dwReturn);
	    lpParms->dwReturn = MAKEMCIRESOURCE(lpParms->dwReturn, lpParms->dwReturn);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_STATUS_MEDIA_PRESENT:
	    lpParms->dwReturn = (MCICDA_GetStatus(wmcda) == MCI_MODE_OPEN) ?
		MAKEMCIRESOURCE(FALSE, MCI_FALSE) : MAKEMCIRESOURCE(TRUE, MCI_TRUE);
	    TRACE("MCI_STATUS_MEDIA_PRESENT =%c!\n", LOWORD(lpParms->dwReturn) ? 'Y' : 'N');
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_STATUS_NUMBER_OF_TRACKS:
	    if (!MCICDA_ReadTOC(wmcda, &toc, &br))
                return MCICDA_GetError(wmcda);

	    lpParms->dwReturn = toc.LastTrack - toc.FirstTrack + 1;
            TRACE("MCI_STATUS_NUMBER_OF_TRACKS = %lu\n", lpParms->dwReturn);
	    if (lpParms->dwReturn == (WORD)-1)
		return MCICDA_GetError(wmcda);
	    break;
	case MCI_STATUS_POSITION:
            switch (dwFlags & (MCI_STATUS_START | MCI_TRACK)) {
            case MCI_STATUS_START:
                if (!MCICDA_ReadTOC(wmcda, &toc, &br))
                    return MCICDA_GetError(wmcda);

		lpParms->dwReturn = FRAME_OF_TOC(toc, toc.FirstTrack);
		TRACE("get MCI_STATUS_START !\n");
                break;
            case MCI_TRACK:
                if (!MCICDA_ReadTOC(wmcda, &toc, &br))
                    return MCICDA_GetError(wmcda);

		if (lpParms->dwTrack < toc.FirstTrack || lpParms->dwTrack > toc.LastTrack)
		    return MCIERR_OUTOFRANGE;
		lpParms->dwReturn = FRAME_OF_TOC(toc, lpParms->dwTrack);
		TRACE("get MCI_TRACK #%u !\n", lpParms->dwTrack);
                break;
            case 0:
                fmt.Format = IOCTL_CDROM_CURRENT_POSITION;
                if (!device_io(wmcda->handle, IOCTL_CDROM_READ_Q_CHANNEL, &fmt, sizeof(fmt),
                                     &data, sizeof(data), &br, NULL)) {
                    return MCICDA_GetError(wmcda);
                }
                lpParms->dwReturn = FRAME_OF_ADDR(data.CurrentPosition.AbsoluteAddress);
                break;
            default:
                return MCIERR_FLAGS_NOT_COMPATIBLE;
            }
	    lpParms->dwReturn = MCICDA_CalcTime(wmcda, wmcda->dwTimeFormat, lpParms->dwReturn, &ret);
            TRACE("MCI_STATUS_POSITION=%08lX\n", lpParms->dwReturn);
	    break;
	case MCI_STATUS_READY:
	    TRACE("MCI_STATUS_READY !\n");
            switch (MCICDA_GetStatus(wmcda))
            {
            case MCI_MODE_NOT_READY:
            case MCI_MODE_OPEN:
                lpParms->dwReturn = MAKEMCIRESOURCE(FALSE, MCI_FALSE);
                break;
            default:
                lpParms->dwReturn = MAKEMCIRESOURCE(TRUE, MCI_TRUE);
                break;
            }
	    TRACE("MCI_STATUS_READY=%u!\n", LOWORD(lpParms->dwReturn));
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_STATUS_TIME_FORMAT:
	    lpParms->dwReturn = MAKEMCIRESOURCE(wmcda->dwTimeFormat, MCI_FORMAT_RETURN_BASE + wmcda->dwTimeFormat);
	    TRACE("MCI_STATUS_TIME_FORMAT=%08x!\n", LOWORD(lpParms->dwReturn));
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case 4001: /* FIXME: for bogus FullCD */
	case MCI_CDA_STATUS_TYPE_TRACK:
	    if (!(dwFlags & MCI_TRACK))
		ret = MCIERR_MISSING_PARAMETER;
	    else {
                if (!MCICDA_ReadTOC(wmcda, &toc, &br))
                    return MCICDA_GetError(wmcda);

		if (lpParms->dwTrack < toc.FirstTrack || lpParms->dwTrack > toc.LastTrack)
		    ret = MCIERR_OUTOFRANGE;
		else
		    lpParms->dwReturn = (toc.TrackData[lpParms->dwTrack - toc.FirstTrack].Control & 0x04) ?
                                         MCI_CDA_TRACK_OTHER : MCI_CDA_TRACK_AUDIO;
		    /* FIXME: MAKEMCIRESOURCE "audio" | "other", localised */
	    }
            TRACE("MCI_CDA_STATUS_TYPE_TRACK[%d]=%ld\n", lpParms->dwTrack, lpParms->dwReturn);
	    break;
	default:
            FIXME("unknown command %08X !\n", lpParms->dwItem);
	    return MCIERR_UNSUPPORTED_FUNCTION;
	}
    } else return MCIERR_MISSING_PARAMETER;
    if ((dwFlags & MCI_NOTIFY) && HRESULT_CODE(ret)==0)
	MCICDA_Notify(lpParms->dwCallback, wmcda, MCI_NOTIFY_SUCCESSFUL);
    return ret;
}