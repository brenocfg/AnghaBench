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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wszZonesKey ; 

__attribute__((used)) static HRESULT open_zone_key(HKEY parent_key, DWORD zone, HKEY *hkey)
{
    static const WCHAR wszFormat[] = {'%','s','%','u',0};

    WCHAR key_name[ARRAY_SIZE(wszZonesKey) + 12];
    DWORD res;

    wsprintfW(key_name, wszFormat, wszZonesKey, zone);

    res = RegOpenKeyW(parent_key, key_name, hkey);

    if(res != ERROR_SUCCESS) {
        WARN("RegOpenKey failed\n");
        return E_INVALIDARG;
    }

    return S_OK;
}