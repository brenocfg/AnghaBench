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
struct TYPE_2__ {int dwEnum; int dwValue; scalar_t__* szValueName; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcmpiW (scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mapEnum ; 

BOOL MSSTYLES_LookupEnum(LPCWSTR pszValueName, int dwEnum, int *dwValue)
{
    DWORD item = 0;
    /* Locate the enum block */
    while(*mapEnum[item].szValueName && mapEnum[item].dwEnum != dwEnum) item++;
    /* Now find the value in that block */
    while(*mapEnum[item].szValueName && mapEnum[item].dwEnum == dwEnum) {
        if(!lstrcmpiW(mapEnum[item].szValueName, pszValueName)) {
            if(dwValue) *dwValue = mapEnum[item].dwValue;
            return TRUE;
        }
        item++;
    }
    return FALSE;
}