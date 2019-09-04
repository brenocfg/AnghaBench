#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szBuffer ;
typedef  char WCHAR ;
struct TYPE_6__ {struct TYPE_6__* pNextACMDriverID; struct TYPE_6__* pPrevACMDriverID; int /*<<< orphan*/  fdwSupport; int /*<<< orphan*/  pszDriverAlias; } ;
typedef  TYPE_1__* PWINE_ACMDRIVERID ;
typedef  int /*<<< orphan*/  LPDWORD ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/ * HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_DISABLED ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 TYPE_1__** HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  MSACM_hHeap ; 
 TYPE_1__* MSACM_pFirstACMDriverID ; 
 TYPE_1__* MSACM_pLastACMDriverID ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  snprintfW (char*,int,char const*,unsigned int) ; 
 scalar_t__ strcmpiW (int /*<<< orphan*/ ,char*) ; 
 char* strstrW (char*,char const*) ; 

__attribute__((used)) static void MSACM_ReorderDriversByPriority(void)
{
    PWINE_ACMDRIVERID	padid;
    unsigned int iNumDrivers;
    PWINE_ACMDRIVERID * driverList = NULL;
    HKEY hPriorityKey = NULL;
    
    TRACE("\n");
    
    /* Count drivers && alloc corresponding memory for list */
    iNumDrivers = 0;
    for (padid = MSACM_pFirstACMDriverID; padid; padid = padid->pNextACMDriverID) iNumDrivers++;
    if (iNumDrivers > 1)
    {
        LONG lError;
        static const WCHAR basePriorityKey[] = {
            'S','o','f','t','w','a','r','e','\\',
            'M','i','c','r','o','s','o','f','t','\\',
            'M','u','l','t','i','m','e','d','i','a','\\',
            'A','u','d','i','o',' ','C','o','m','p','r','e','s','s','i','o','n',' ','M','a','n','a','g','e','r','\\',
            'P','r','i','o','r','i','t','y',' ','v','4','.','0','0','\0'
        };
        unsigned int i;
        LONG lBufferLength;
        WCHAR szBuffer[256];
        
        driverList = HeapAlloc(MSACM_hHeap, 0, iNumDrivers * sizeof(PWINE_ACMDRIVERID));
        if (!driverList)
        {
            ERR("out of memory\n");
            goto errCleanUp;
        }

        lError = RegOpenKeyW(HKEY_CURRENT_USER, basePriorityKey, &hPriorityKey);
        if (lError != ERROR_SUCCESS) {
            TRACE("RegOpenKeyW failed, possibly key does not exist yet\n");
            hPriorityKey = NULL;
            goto errCleanUp;
        } 
            
        /* Copy drivers into list to simplify linked list modification */
        for (i = 0, padid = MSACM_pFirstACMDriverID; padid; padid = padid->pNextACMDriverID, i++)
        {
            driverList[i] = padid;
        }

        /* Query each of the priorities in turn. Alias key is in lowercase. 
            The general form of the priority record is the following:
            "PriorityN" --> "1, msacm.driveralias"
            where N is an integer, and the value is a string of the driver
            alias, prefixed by "1, " for an enabled driver, or "0, " for a
            disabled driver.
            */
        for (i = 0; i < iNumDrivers; i++)
        {
            static const WCHAR priorityTmpl[] = {'P','r','i','o','r','i','t','y','%','l','d','\0'};
            WCHAR szSubKey[17];
            unsigned int iTargetPosition;
            unsigned int iCurrentPosition;
            WCHAR * pAlias;
            static const WCHAR sPrefix[] = {'m','s','a','c','m','.','\0'};
            
            /* Build expected entry name */
            snprintfW(szSubKey, 17, priorityTmpl, i + 1);
            lBufferLength = sizeof(szBuffer);
            lError = RegQueryValueExW(hPriorityKey, szSubKey, NULL, NULL, (LPBYTE)szBuffer, (LPDWORD)&lBufferLength);
            if (lError != ERROR_SUCCESS) continue;

            /* Recovered driver alias should be at this position */
            iTargetPosition = i;
            
            /* Locate driver alias in driver list */
            pAlias = strstrW(szBuffer, sPrefix);
            if (pAlias == NULL) continue;
            
            for (iCurrentPosition = 0; iCurrentPosition < iNumDrivers; iCurrentPosition++) {
                if (strcmpiW(driverList[iCurrentPosition]->pszDriverAlias, pAlias) == 0) 
                    break;
            }
            if (iCurrentPosition < iNumDrivers && iTargetPosition != iCurrentPosition) {
                padid = driverList[iTargetPosition];
                driverList[iTargetPosition] = driverList[iCurrentPosition];
                driverList[iCurrentPosition] = padid;

                /* Locate enabled status */
                if (szBuffer[0] == '1') {
                    driverList[iTargetPosition]->fdwSupport &= ~ACMDRIVERDETAILS_SUPPORTF_DISABLED;
                } else if (szBuffer[0] == '0') {
                    driverList[iTargetPosition]->fdwSupport |= ACMDRIVERDETAILS_SUPPORTF_DISABLED;
                }
            }
        }
        
        /* Re-assign pointers so that linked list traverses the ordered array */
        for (i = 0; i < iNumDrivers; i++) {
            driverList[i]->pPrevACMDriverID = (i > 0) ? driverList[i - 1] : NULL;
            driverList[i]->pNextACMDriverID = (i < iNumDrivers - 1) ? driverList[i + 1] : NULL;
        }
        MSACM_pFirstACMDriverID = driverList[0];
        MSACM_pLastACMDriverID = driverList[iNumDrivers - 1];
    }
    
errCleanUp:
    if (hPriorityKey != NULL) RegCloseKey(hPriorityKey);
    HeapFree(MSACM_hHeap, 0, driverList);
}