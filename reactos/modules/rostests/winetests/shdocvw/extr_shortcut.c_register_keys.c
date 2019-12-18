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
struct registry_value {int /*<<< orphan*/  dwType; int /*<<< orphan*/  szName; } ;
struct registry_key {unsigned int cValues; unsigned int cSubKeys; struct registry_key* pSubKeys; struct registry_value* pValues; int /*<<< orphan*/  szName; } ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  REG_VALUE_ADDR (struct registry_value const*) ; 
 int /*<<< orphan*/  REG_VALUE_SIZE (struct registry_value const*) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL register_keys(HKEY hRootKey, const struct registry_key *keys, unsigned int numKeys) {
    HKEY hKey;
    unsigned int iKey, iValue;

    for (iKey = 0; iKey < numKeys; iKey++) {
        if (ERROR_SUCCESS == RegCreateKeyExA(hRootKey, keys[iKey].szName, 0, NULL, 0, 
                                             KEY_WRITE, NULL, &hKey, NULL))
        {
            for (iValue = 0; iValue < keys[iKey].cValues; iValue++) {
                const struct registry_value * value = &keys[iKey].pValues[iValue];
                if (ERROR_SUCCESS != RegSetValueExA(hKey, value->szName, 0, value->dwType,
                                                    REG_VALUE_ADDR(value), REG_VALUE_SIZE(value)))
                {
                    RegCloseKey(hKey);
                    return FALSE;
                }
            }
            
            if (!register_keys(hKey, keys[iKey].pSubKeys, keys[iKey].cSubKeys)) {
                RegCloseKey(hKey);
                return FALSE;
            }
            
            RegCloseKey(hKey);
        }
    }
        
    return TRUE;
}