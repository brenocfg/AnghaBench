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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  TYPE_1__ DMO_PARTIAL_MEDIATYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CLSIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int MSDMO_MAJOR_VERSION ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szToGuidFmt ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HRESULT read_types(HKEY root, LPCWSTR key, ULONG *supplied, ULONG requested, DMO_PARTIAL_MEDIATYPE* types )
{
    HRESULT ret = S_OK;

    if (MSDMO_MAJOR_VERSION > 5)
    {
        DWORD len;
        LONG rc;

        len = requested * sizeof(DMO_PARTIAL_MEDIATYPE);
        rc = RegQueryValueExW(root, key, NULL, NULL, (LPBYTE) types, &len);
        ret = HRESULT_FROM_WIN32(rc);

        *supplied = len / sizeof(DMO_PARTIAL_MEDIATYPE);
    }
    else
    {
        HKEY hkey;
        WCHAR szGuidKey[64];

        *supplied = 0;
        if (ERROR_SUCCESS == RegOpenKeyExW(root, key, 0, KEY_READ, &hkey))
        {
          int index = 0;
          WCHAR szNextKey[MAX_PATH];
          DWORD len;
          LONG rc = ERROR_SUCCESS;

          while (rc == ERROR_SUCCESS)
          {
            len = MAX_PATH;
            rc = RegEnumKeyExW(hkey, index, szNextKey, &len, NULL, NULL, NULL, NULL);
            if (rc == ERROR_SUCCESS)
            {
              HKEY subk;
              int sub_index = 0;
              LONG rcs = ERROR_SUCCESS;
              WCHAR szSubKey[MAX_PATH];

              RegOpenKeyExW(hkey, szNextKey, 0, KEY_READ, &subk);
              while (rcs == ERROR_SUCCESS)
              {
                len = MAX_PATH;
                rcs = RegEnumKeyExW(subk, sub_index, szSubKey, &len, NULL, NULL, NULL, NULL);
                if (rcs == ERROR_SUCCESS)
                {
                  if (*supplied >= requested)
                  {
                    /* Bailing */
                    ret = S_FALSE;
                    rc = ERROR_MORE_DATA;
                    rcs = ERROR_MORE_DATA;
                    break;
                  }

                  wsprintfW(szGuidKey,szToGuidFmt,szNextKey);
                  CLSIDFromString(szGuidKey, &types[*supplied].type);
                  wsprintfW(szGuidKey,szToGuidFmt,szSubKey);
                  CLSIDFromString(szGuidKey, &types[*supplied].subtype);
                  TRACE("Adding type %s subtype %s at index %i\n",
                    debugstr_guid(&types[*supplied].type),
                    debugstr_guid(&types[*supplied].subtype),
                    *supplied);
                  (*supplied)++;
                }
                sub_index++;
              }
              index++;
            }
          }
          RegCloseKey(hkey);
        }
    }
    return ret;
}