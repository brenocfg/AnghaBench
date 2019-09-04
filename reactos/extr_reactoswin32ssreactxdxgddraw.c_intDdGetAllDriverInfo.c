#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int dwFlags; scalar_t__ GetDriverInfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  dwCallbackFlags; int /*<<< orphan*/  ddMotionCompCallbacks; int /*<<< orphan*/  ddNtPrivateDriverCaps; int /*<<< orphan*/  ddMoreCaps; int /*<<< orphan*/  ddNtCallbacks; int /*<<< orphan*/  ddMiscellanous2Callbacks; int /*<<< orphan*/  ddMiscellanousCallbacks; int /*<<< orphan*/  ddColorControlCallbacks; int /*<<< orphan*/  d3dNtHalCallbacks3; int /*<<< orphan*/  ddKernelCallbacks; int /*<<< orphan*/  ddKernelCaps; TYPE_1__ ddHalInfo; } ;
typedef  TYPE_2__* PEDD_DIRECTDRAW_GLOBAL ;

/* Variables and functions */
 int DDHALINFO_GETDRIVERINFOSET ; 
 int /*<<< orphan*/  EDDDGBL_COLORCONTROLCALLBACKS ; 
 int /*<<< orphan*/  EDDDGBL_D3DCALLBACKS3 ; 
 int /*<<< orphan*/  EDDDGBL_DDMORECAPS ; 
 int /*<<< orphan*/  EDDDGBL_MISC2CALLBACKS ; 
 int /*<<< orphan*/  EDDDGBL_MISCCALLBACKS ; 
 int /*<<< orphan*/  EDDDGBL_MOTIONCOMPCALLBACKS ; 
 int /*<<< orphan*/  EDDDGBL_NTCALLBACKS ; 
 int /*<<< orphan*/  EDDDGBL_PRIVATEDRIVERCAPS ; 
 int /*<<< orphan*/  GUID_ColorControlCallbacks ; 
 int /*<<< orphan*/  GUID_D3DCallbacks3 ; 
 int /*<<< orphan*/  GUID_DDMoreCaps ; 
 int /*<<< orphan*/  GUID_KernelCallbacks ; 
 int /*<<< orphan*/  GUID_KernelCaps ; 
 int /*<<< orphan*/  GUID_Miscellaneous2Callbacks ; 
 int /*<<< orphan*/  GUID_MiscellaneousCallbacks ; 
 int /*<<< orphan*/  GUID_MotionCompCallbacks ; 
 int /*<<< orphan*/  GUID_NTCallbacks ; 
 int /*<<< orphan*/  GUID_NTPrivateDriverCaps ; 
 scalar_t__ intDdGetDriverInfo (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

VOID intDdGetAllDriverInfo(PEDD_DIRECTDRAW_GLOBAL peDdGl)
{
    if (peDdGl->ddHalInfo.GetDriverInfo && peDdGl->ddHalInfo.dwFlags & DDHALINFO_GETDRIVERINFOSET)
    {
        intDdGetDriverInfo(peDdGl, GUID_KernelCaps, &peDdGl->ddKernelCaps, sizeof(peDdGl->ddKernelCaps), 0);
        intDdGetDriverInfo(peDdGl, GUID_KernelCallbacks, &peDdGl->ddKernelCallbacks, sizeof(peDdGl->ddKernelCallbacks), 0);

        if (intDdGetDriverInfo(peDdGl, GUID_D3DCallbacks3, &peDdGl->d3dNtHalCallbacks3, sizeof(peDdGl->d3dNtHalCallbacks3), 0))
            peDdGl->dwCallbackFlags |= EDDDGBL_D3DCALLBACKS3;

        if (intDdGetDriverInfo(peDdGl, GUID_ColorControlCallbacks, &peDdGl->ddColorControlCallbacks, sizeof(peDdGl->ddColorControlCallbacks), 0))
            peDdGl->dwCallbackFlags |= EDDDGBL_COLORCONTROLCALLBACKS;

        if (intDdGetDriverInfo(peDdGl, GUID_MiscellaneousCallbacks, &peDdGl->ddMiscellanousCallbacks, sizeof(peDdGl->ddMiscellanousCallbacks), 0))
            peDdGl->dwCallbackFlags |= EDDDGBL_MISCCALLBACKS;

        if (intDdGetDriverInfo(peDdGl, GUID_Miscellaneous2Callbacks, &peDdGl->ddMiscellanous2Callbacks, sizeof(peDdGl->ddMiscellanous2Callbacks), 0))
            peDdGl->dwCallbackFlags |= EDDDGBL_MISC2CALLBACKS;

        if (intDdGetDriverInfo(peDdGl, GUID_NTCallbacks, &peDdGl->ddNtCallbacks, sizeof(peDdGl->ddNtCallbacks), 0) )
            peDdGl->dwCallbackFlags |= EDDDGBL_NTCALLBACKS;

        if (intDdGetDriverInfo(peDdGl, GUID_DDMoreCaps, &peDdGl->ddMoreCaps, sizeof(peDdGl->ddMoreCaps), 0) )
            peDdGl->dwCallbackFlags |= EDDDGBL_DDMORECAPS;

        if (intDdGetDriverInfo(peDdGl, GUID_NTPrivateDriverCaps, &peDdGl->ddNtPrivateDriverCaps, sizeof(peDdGl->ddNtPrivateDriverCaps), 0) )
            peDdGl->dwCallbackFlags |= EDDDGBL_PRIVATEDRIVERCAPS;

        if (intDdGetDriverInfo(peDdGl, GUID_MotionCompCallbacks, &peDdGl->ddMotionCompCallbacks, sizeof(peDdGl->ddMotionCompCallbacks), 0) )
            peDdGl->dwCallbackFlags |= EDDDGBL_MOTIONCOMPCALLBACKS;
    }
}