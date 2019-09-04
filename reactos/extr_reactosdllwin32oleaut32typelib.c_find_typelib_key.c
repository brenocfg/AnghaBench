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
typedef  int /*<<< orphan*/  typelibW ;
typedef  int /*<<< orphan*/  key_name ;
typedef  int WORD ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  REFGUID ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int sscanf (char*,char*,scalar_t__*,scalar_t__*) ; 
 int strlenW (char*) ; 

__attribute__((used)) static BOOL find_typelib_key( REFGUID guid, WORD *wMaj, WORD *wMin )
{
    static const WCHAR typelibW[] = {'T','y','p','e','l','i','b','\\',0};
    WCHAR buffer[60];
    char key_name[16];
    DWORD len, i;
    INT best_maj = -1, best_min = -1;
    HKEY hkey;

    memcpy( buffer, typelibW, sizeof(typelibW) );
    StringFromGUID2( guid, buffer + strlenW(buffer), 40 );

    if (RegOpenKeyExW( HKEY_CLASSES_ROOT, buffer, 0, KEY_READ, &hkey ) != ERROR_SUCCESS)
        return FALSE;

    len = sizeof(key_name);
    i = 0;
    while (RegEnumKeyExA(hkey, i++, key_name, &len, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
    {
        INT v_maj, v_min;

        if (sscanf(key_name, "%x.%x", &v_maj, &v_min) == 2)
        {
            TRACE("found %s: %x.%x\n", debugstr_w(buffer), v_maj, v_min);

            if (*wMaj == 0xffff && *wMin == 0xffff)
            {
                if (v_maj > best_maj) best_maj = v_maj;
                if (v_min > best_min) best_min = v_min;
            }
            else if (*wMaj == v_maj)
            {
                best_maj = v_maj;

                if (*wMin == v_min)
                {
                    best_min = v_min;
                    break; /* exact match */
                }
                if (*wMin != 0xffff && v_min > best_min) best_min = v_min;
            }
        }
        len = sizeof(key_name);
    }
    RegCloseKey( hkey );

    TRACE("found best_maj %d, best_min %d\n", best_maj, best_min);

    if (*wMaj == 0xffff && *wMin == 0xffff)
    {
        if (best_maj >= 0 && best_min >= 0)
        {
            *wMaj = best_maj;
            *wMin = best_min;
            return TRUE;
        }
    }

    if (*wMaj == best_maj && best_min >= 0)
    {
        *wMin = best_min;
        return TRUE;
    }
    return FALSE;
}