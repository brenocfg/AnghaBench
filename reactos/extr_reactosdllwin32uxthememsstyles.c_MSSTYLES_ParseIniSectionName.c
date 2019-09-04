#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  sec ;
typedef  int /*<<< orphan*/  part ;
typedef  char WCHAR ;
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MAX_THEME_APP_NAME ; 
 int MAX_THEME_CLASS_NAME ; 
 int /*<<< orphan*/  MSSTYLES_LookupPartState (char*,char*,char*,int*,int*) ; 
 int /*<<< orphan*/  lstrcpynW (char*,char*,int) ; 
 int min (scalar_t__,int) ; 
 char* strchrW (char*,char) ; 

__attribute__((used)) static BOOL MSSTYLES_ParseIniSectionName(LPCWSTR lpSection, DWORD dwLen, LPWSTR szAppName, LPWSTR szClassName, int *iPartId, int *iStateId)
{
    WCHAR sec[255];
    WCHAR part[60] = {'\0'};
    WCHAR state[60] = {'\0'};
    LPWSTR tmp;
    LPWSTR comp;
    lstrcpynW(sec, lpSection, min(dwLen+1, sizeof(sec)/sizeof(sec[0])));

    *szAppName = 0;
    *szClassName = 0;
    *iPartId = 0;
    *iStateId = 0;
    comp = sec;
    /* Get the application name */
    tmp = strchrW(comp, ':');
    if(tmp) {
        *tmp++ = 0;
        tmp++;
        lstrcpynW(szAppName, comp, MAX_THEME_APP_NAME);
        comp = tmp;
    }

    tmp = strchrW(comp, '.');
    if(tmp) {
        *tmp++ = 0;
        lstrcpynW(szClassName, comp, MAX_THEME_CLASS_NAME);
        comp = tmp;
        /* now get the part & state */
        tmp = strchrW(comp, '(');
        if(tmp) {
            *tmp++ = 0;
            lstrcpynW(part, comp, sizeof(part)/sizeof(part[0]));
            comp = tmp;
            /* now get the state */
            tmp = strchrW(comp, ')');
            if (!tmp)
                return FALSE;
            *tmp = 0;
            lstrcpynW(state, comp, sizeof(state)/sizeof(state[0]));
        }
        else {
            lstrcpynW(part, comp, sizeof(part)/sizeof(part[0]));
        }
    }
    else {
        tmp = strchrW(comp, '(');
        if(tmp) {
            *tmp++ = 0;
            lstrcpynW(szClassName, comp, MAX_THEME_CLASS_NAME);
            comp = tmp;
            /* now get the state */
            tmp = strchrW(comp, ')');
            if (!tmp)
                return FALSE;
            *tmp = 0;
            lstrcpynW(state, comp, sizeof(state)/sizeof(state[0]));
        }
        else {
            lstrcpynW(szClassName, comp, MAX_THEME_CLASS_NAME);
        }
    }
    if(!*szClassName) return FALSE;
    return MSSTYLES_LookupPartState(szClassName, part[0]?part:NULL, state[0]?state:NULL, iPartId, iStateId);
}