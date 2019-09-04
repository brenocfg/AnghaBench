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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ CoInternetGetSecurityUrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateUri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PSU_SECURITY_URL_ONLY ; 
 scalar_t__ S_OK ; 
 int URLZONE_INVALID ; 
 int /*<<< orphan*/  Uri_CREATE_ALLOW_IMPLICIT_FILE_SCHEME ; 
 scalar_t__ map_security_uri_to_zone (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT map_url_to_zone(LPCWSTR url, DWORD *zone, LPWSTR *ret_url)
{
    IUri *secur_uri;
    LPWSTR secur_url;
    HRESULT hres;

    *zone = URLZONE_INVALID;

    hres = CoInternetGetSecurityUrl(url, &secur_url, PSU_SECURITY_URL_ONLY, 0);
    if(hres != S_OK) {
        DWORD size = strlenW(url)*sizeof(WCHAR);

        secur_url = CoTaskMemAlloc(size);
        if(!secur_url)
            return E_OUTOFMEMORY;

        memcpy(secur_url, url, size);
    }

    hres = CreateUri(secur_url, Uri_CREATE_ALLOW_IMPLICIT_FILE_SCHEME, 0, &secur_uri);
    if(FAILED(hres)) {
        CoTaskMemFree(secur_url);
        return hres;
    }

    hres = map_security_uri_to_zone(secur_uri, zone);
    IUri_Release(secur_uri);

    if(FAILED(hres) || !ret_url)
        CoTaskMemFree(secur_url);
    else
        *ret_url = secur_url;

    return hres;
}