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
typedef  char WCHAR ;
typedef  int* LPDWORD ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegEnumKeyExW (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int atoiW (char*) ; 
 int* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int*) ; 
 int* heap_realloc_zero (int*,int) ; 
 int /*<<< orphan*/  wszZonesKey ; 

__attribute__((used)) static LPDWORD build_zonemap_from_reg(void)
{
    WCHAR name[32];
    HKEY hkey;
    LPDWORD data = NULL;
    DWORD allocated = 6; /* space for the zonecount and Zone "0" up to Zone "4" */
    DWORD used = 0;
    DWORD res;
    DWORD len;


    res = RegOpenKeyW(HKEY_CURRENT_USER, wszZonesKey, &hkey);
    if (res)
        return NULL;

    data = heap_alloc(allocated * sizeof(DWORD));
    if (!data)
        goto cleanup;

    while (!res) {
        name[0] = '\0';
        len = ARRAY_SIZE(name);
        res = RegEnumKeyExW(hkey, used, name, &len, NULL, NULL, NULL, NULL);

        if (!res) {
            used++;
            if (used == allocated) {
                LPDWORD new_data;

                allocated *= 2;
                new_data = heap_realloc_zero(data, allocated * sizeof(DWORD));
                if (!new_data)
                    goto cleanup;

                data = new_data;
            }
            data[used] = atoiW(name);
        }
    }
    if (used) {
        RegCloseKey(hkey);
        data[0] = used;
        return data;
    }

cleanup:
    /* something failed */
    RegCloseKey(hkey);
    heap_free(data);
    return NULL;
}