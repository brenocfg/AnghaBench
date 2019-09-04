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
typedef  char WCHAR ;
struct TYPE_3__ {int fdwSupport; char const* pszDriverAlias; struct TYPE_3__* pNextACMDriverID; } ;
typedef  TYPE_1__* PWINE_ACMDRIVERID ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ACMDRIVERDETAILS_SUPPORTF_DISABLED ; 
 int ACMDRIVERDETAILS_SUPPORTF_LOCAL ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 TYPE_1__* MSACM_pFirstACMDriverID ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegDeleteKeyW (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  snprintfW (char*,int,char const*,char,...) ; 
 int strlenW (char*) ; 
 int /*<<< orphan*/  strlwrW (char*) ; 

void MSACM_WriteCurrentPriorities(void)
{
    LONG lError;
    HKEY hPriorityKey;
    static const WCHAR basePriorityKey[] = {
        'S','o','f','t','w','a','r','e','\\',
        'M','i','c','r','o','s','o','f','t','\\',
        'M','u','l','t','i','m','e','d','i','a','\\',
        'A','u','d','i','o',' ','C','o','m','p','r','e','s','s','i','o','n',' ','M','a','n','a','g','e','r','\\',
        'P','r','i','o','r','i','t','y',' ','v','4','.','0','0','\0'
    };
    PWINE_ACMDRIVERID padid;
    DWORD dwPriorityCounter;
    static const WCHAR priorityTmpl[] = {'P','r','i','o','r','i','t','y','%','l','d','\0'};
    static const WCHAR valueTmpl[] = {'%','c',',',' ','%','s','\0'};
    static const WCHAR converterAlias[] = {'I','n','t','e','r','n','a','l',' ','P','C','M',' ','C','o','n','v','e','r','t','e','r','\0'};
    WCHAR szSubKey[17];
    WCHAR szBuffer[256];

    /* Delete ACM priority key and create it anew */
    lError = RegDeleteKeyW(HKEY_CURRENT_USER, basePriorityKey);
    if (lError != ERROR_SUCCESS && lError != ERROR_FILE_NOT_FOUND) {
        ERR("unable to remove current key %s (0x%08x) - priority changes won't persist past application end.\n",
            debugstr_w(basePriorityKey), lError);
        return;
    }
    lError = RegCreateKeyW(HKEY_CURRENT_USER, basePriorityKey, &hPriorityKey);
    if (lError != ERROR_SUCCESS) {
        ERR("unable to create key %s (0x%08x) - priority changes won't persist past application end.\n",
            debugstr_w(basePriorityKey), lError);
        return;
    }
    
    /* Write current list of priorities */
    for (dwPriorityCounter = 0, padid = MSACM_pFirstACMDriverID; padid; padid = padid->pNextACMDriverID) {        
        if (padid->fdwSupport & ACMDRIVERDETAILS_SUPPORTF_LOCAL) continue;
        if (padid->pszDriverAlias == NULL) continue;    /* internal PCM converter is last */

        /* Build required value name */
        dwPriorityCounter++;
        snprintfW(szSubKey, 17, priorityTmpl, dwPriorityCounter);
        
        /* Value has a 1 in front for enabled drivers and 0 for disabled drivers */
        snprintfW(szBuffer, 256, valueTmpl, (padid->fdwSupport & ACMDRIVERDETAILS_SUPPORTF_DISABLED) ? '0' : '1', padid->pszDriverAlias);
        strlwrW(szBuffer);
        
        lError = RegSetValueExW(hPriorityKey, szSubKey, 0, REG_SZ, (BYTE *)szBuffer, (strlenW(szBuffer) + 1) * sizeof(WCHAR));
        if (lError != ERROR_SUCCESS) {
            ERR("unable to write value for %s under key %s (0x%08x)\n",
                debugstr_w(padid->pszDriverAlias), debugstr_w(basePriorityKey), lError);
        }
    }
    
    /* Build required value name */
    dwPriorityCounter++;
    snprintfW(szSubKey, 17, priorityTmpl, dwPriorityCounter);
        
    /* Value has a 1 in front for enabled drivers and 0 for disabled drivers */
    snprintfW(szBuffer, 256, valueTmpl, '1', converterAlias);
        
    lError = RegSetValueExW(hPriorityKey, szSubKey, 0, REG_SZ, (BYTE *)szBuffer, (strlenW(szBuffer) + 1) * sizeof(WCHAR));
    if (lError != ERROR_SUCCESS) {
        ERR("unable to write value for %s under key %s (0x%08x)\n",
            debugstr_w(converterAlias), debugstr_w(basePriorityKey), lError);
    }
    RegCloseKey(hPriorityKey);
}