#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fdwSupport; struct TYPE_5__* pPrevACMDriverID; struct TYPE_5__* pNextACMDriverID; } ;
typedef  TYPE_1__* PWINE_ACMDRIVERID ;
typedef  int DWORD ;

/* Variables and functions */
 int ACMDRIVERDETAILS_SUPPORTF_LOCAL ; 
 TYPE_1__* MSACM_pFirstACMDriverID ; 
 TYPE_1__* MSACM_pLastACMDriverID ; 

void MSACM_RePositionDriver(PWINE_ACMDRIVERID padid, DWORD dwPriority)
{
    PWINE_ACMDRIVERID pTargetPosition = NULL;
                
    /* Remove selected driver from linked list */
    if (MSACM_pFirstACMDriverID == padid) {
        MSACM_pFirstACMDriverID = padid->pNextACMDriverID;
    }
    if (MSACM_pLastACMDriverID == padid) {
        MSACM_pLastACMDriverID = padid->pPrevACMDriverID;
    }
    if (padid->pPrevACMDriverID != NULL) {
        padid->pPrevACMDriverID->pNextACMDriverID = padid->pNextACMDriverID;
    }
    if (padid->pNextACMDriverID != NULL) {
        padid->pNextACMDriverID->pPrevACMDriverID = padid->pPrevACMDriverID;
    }
    
    /* Look up position where selected driver should be */
    if (dwPriority == 1) {
        pTargetPosition = padid->pPrevACMDriverID;
        while (pTargetPosition->pPrevACMDriverID != NULL &&
            !(pTargetPosition->pPrevACMDriverID->fdwSupport & ACMDRIVERDETAILS_SUPPORTF_LOCAL)) {
            pTargetPosition = pTargetPosition->pPrevACMDriverID;
        }
    } else if (dwPriority == -1) {
        pTargetPosition = padid->pNextACMDriverID;
        while (pTargetPosition->pNextACMDriverID != NULL) {
            pTargetPosition = pTargetPosition->pNextACMDriverID;
        }
    }
    
    /* Place selected driver in selected position */
    padid->pPrevACMDriverID = pTargetPosition->pPrevACMDriverID;
    padid->pNextACMDriverID = pTargetPosition;
    if (padid->pPrevACMDriverID != NULL) {
        padid->pPrevACMDriverID->pNextACMDriverID = padid;
    } else {
        MSACM_pFirstACMDriverID = padid;
    }
    if (padid->pNextACMDriverID != NULL) {
        padid->pNextACMDriverID->pPrevACMDriverID = padid;
    } else {
        MSACM_pLastACMDriverID = padid;
    }
}