#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dwPrimitiveType; int dwPropertyID; scalar_t__* szPropertyName; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcmpiW (scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mapProperty ; 

BOOL MSSTYLES_LookupProperty(LPCWSTR pszPropertyName, int *dwPrimitive, int *dwId)
{
    DWORD item = 0;
    do {
        if(!lstrcmpiW(mapProperty[item].szPropertyName, pszPropertyName)) {
            if(dwPrimitive) *dwPrimitive = mapProperty[item].dwPrimitiveType;
            if(dwId) *dwId = mapProperty[item].dwPropertyID;
            return TRUE;
        }
    } while(*mapProperty[++item].szPropertyName);
    return FALSE;
}