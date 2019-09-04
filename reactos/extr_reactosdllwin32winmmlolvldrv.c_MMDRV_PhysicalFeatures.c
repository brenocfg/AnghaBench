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
struct TYPE_7__ {int /*<<< orphan*/  bIsMapper; int /*<<< orphan*/  drvname; } ;
typedef  TYPE_1__ WINE_MM_DRIVER ;
typedef  int UINT ;
struct TYPE_8__ {size_t mmdIndex; } ;
typedef  TYPE_2__* LPWINE_MLD ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int* LPDWORD ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
#define  DRVM_MAPPER_PREFERRED_GET 137 
#define  DRV_QUERYDEVICEINTERFACE 136 
#define  DRV_QUERYDEVICEINTERFACESIZE 135 
#define  DRV_QUERYDEVNODE 134 
#define  DRV_QUERYDRIVERIDS 133 
#define  DRV_QUERYDRVENTRY 132 
#define  DRV_QUERYDSOUNDDESC 131 
#define  DRV_QUERYDSOUNDIFACE 130 
#define  DRV_QUERYMAPPABLE 129 
#define  DRV_QUERYNAME 128 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int MMDRV_Message (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* MMDrvs ; 
 int MMSYSERR_INVALPARAM ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  lstrcpynA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT	MMDRV_PhysicalFeatures(LPWINE_MLD mld, UINT uMsg,
                               DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    WINE_MM_DRIVER*	lpDrv = &MMDrvs[mld->mmdIndex];

    TRACE("(%p, %04x, %08lx, %08lx)\n", mld, uMsg, dwParam1, dwParam2);

    /* all those function calls are undocumented */
    switch (uMsg) {
    case DRV_QUERYDRVENTRY:
        lstrcpynA((LPSTR)dwParam1, lpDrv->drvname, LOWORD(dwParam2));
	break;
    case DRV_QUERYDEVNODE:
        *(LPDWORD)dwParam1 = 0L; /* should be DevNode */
	break;
    case DRV_QUERYNAME:
	WARN("NIY QueryName\n");
	break;
    case DRV_QUERYDRIVERIDS:
	WARN("NIY call VxD\n");
	/* should call VxD MMDEVLDR with (DevNode, dwParam1 and dwParam2) as pmts
	 * dwParam1 is buffer and dwParam2 is sizeof(buffer)
	 * I don't know where the result is stored though
	 */
	break;
    case DRV_QUERYMAPPABLE:
	return (lpDrv->bIsMapper) ? 2 : 0;

    case DRVM_MAPPER_PREFERRED_GET:
	/* FIXME: get from registry someday */
        *((LPDWORD)dwParam1) = -1;      /* No preferred device */
        *((LPDWORD)dwParam2) = 0;
        break;

    case DRV_QUERYDEVICEINTERFACE:
    case DRV_QUERYDEVICEINTERFACESIZE:
        return MMDRV_Message(mld, uMsg, dwParam1, dwParam2);

    case DRV_QUERYDSOUNDIFACE: /* Wine-specific: Retrieve DirectSound interface */
    case DRV_QUERYDSOUNDDESC: /* Wine-specific: Retrieve DirectSound driver description*/
	return MMDRV_Message(mld, uMsg, dwParam1, dwParam2);

    default:
	WARN("Unknown call %04x\n", uMsg);
	return MMSYSERR_INVALPARAM;
    }
    return 0L;
}