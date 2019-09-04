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
typedef  int /*<<< orphan*/  WINE_MCICDAUDIO ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int dwItem; int dwReturn; int /*<<< orphan*/  dwCallback; } ;
typedef  TYPE_1__* LPMCI_GETDEVCAPS_PARMS ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* MAKEMCIRESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCICDA_Notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MCIERR_INVALID_DEVICE_ID ; 
 int MCIERR_MISSING_PARAMETER ; 
 int MCIERR_NULL_PARAMETER_BLOCK ; 
 int MCIERR_UNSUPPORTED_FUNCTION ; 
 int /*<<< orphan*/  MCI_DEVTYPE_CD_AUDIO ; 
 int /*<<< orphan*/  MCI_FALSE ; 
#define  MCI_GETDEVCAPS_CAN_EJECT 136 
#define  MCI_GETDEVCAPS_CAN_PLAY 135 
#define  MCI_GETDEVCAPS_CAN_RECORD 134 
#define  MCI_GETDEVCAPS_CAN_SAVE 133 
#define  MCI_GETDEVCAPS_COMPOUND_DEVICE 132 
#define  MCI_GETDEVCAPS_DEVICE_TYPE 131 
#define  MCI_GETDEVCAPS_HAS_AUDIO 130 
#define  MCI_GETDEVCAPS_HAS_VIDEO 129 
 int MCI_GETDEVCAPS_ITEM ; 
#define  MCI_GETDEVCAPS_USES_FILES 128 
 int MCI_NOTIFY ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 int MCI_RESOURCE_RETURNED ; 
 int /*<<< orphan*/  MCI_TRUE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 scalar_t__ mciGetDriverData (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD MCICDA_GetDevCaps(UINT wDevID, DWORD dwFlags,
				   LPMCI_GETDEVCAPS_PARMS lpParms)
{
    WINE_MCICDAUDIO* 	wmcda = (WINE_MCICDAUDIO*)mciGetDriverData(wDevID);
    DWORD	ret = 0;

    TRACE("(%04X, %08X, %p);\n", wDevID, dwFlags, lpParms);

    if (lpParms == NULL) return MCIERR_NULL_PARAMETER_BLOCK;
    if (wmcda == NULL)			return MCIERR_INVALID_DEVICE_ID;

    if (dwFlags & MCI_GETDEVCAPS_ITEM) {
	TRACE("MCI_GETDEVCAPS_ITEM dwItem=%08X;\n", lpParms->dwItem);

	switch (lpParms->dwItem) {
	case MCI_GETDEVCAPS_CAN_RECORD:
	    lpParms->dwReturn = MAKEMCIRESOURCE(FALSE, MCI_FALSE);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_GETDEVCAPS_HAS_AUDIO:
	    lpParms->dwReturn = MAKEMCIRESOURCE(TRUE, MCI_TRUE);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_GETDEVCAPS_HAS_VIDEO:
	    lpParms->dwReturn = MAKEMCIRESOURCE(FALSE, MCI_FALSE);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_GETDEVCAPS_DEVICE_TYPE:
	    lpParms->dwReturn = MAKEMCIRESOURCE(MCI_DEVTYPE_CD_AUDIO, MCI_DEVTYPE_CD_AUDIO);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_GETDEVCAPS_USES_FILES:
	    lpParms->dwReturn = MAKEMCIRESOURCE(FALSE, MCI_FALSE);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_GETDEVCAPS_COMPOUND_DEVICE:
	    lpParms->dwReturn = MAKEMCIRESOURCE(FALSE, MCI_FALSE);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_GETDEVCAPS_CAN_EJECT:
	    lpParms->dwReturn = MAKEMCIRESOURCE(TRUE, MCI_TRUE);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_GETDEVCAPS_CAN_PLAY:
	    lpParms->dwReturn = MAKEMCIRESOURCE(TRUE, MCI_TRUE);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	case MCI_GETDEVCAPS_CAN_SAVE:
	    lpParms->dwReturn = MAKEMCIRESOURCE(FALSE, MCI_FALSE);
	    ret = MCI_RESOURCE_RETURNED;
	    break;
	default:
            WARN("Unsupported %x devCaps item\n", lpParms->dwItem);
	    return MCIERR_UNSUPPORTED_FUNCTION;
	}
    } else {
	TRACE("No GetDevCaps-Item !\n");
	return MCIERR_MISSING_PARAMETER;
    }
    TRACE("lpParms->dwReturn=%08X;\n", lpParms->dwReturn);
    if (dwFlags & MCI_NOTIFY) {
	MCICDA_Notify(lpParms->dwCallback, wmcda, MCI_NOTIFY_SUCCESSFUL);
    }
    return ret;
}