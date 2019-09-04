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
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_NOT_SUFFICIENT_BUFFER ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_GetDisplayUri (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUri_GetHost (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUri_GetScheme (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IUri_GetSchemeName (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 scalar_t__ URLZONE_INVALID ; 
 scalar_t__ URL_SCHEME_WILDCARD ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_hierarchical_scheme (scalar_t__) ; 

__attribute__((used)) static HRESULT generate_security_id(IUri *uri, BYTE *secid, DWORD *secid_len, DWORD zone)
{
    DWORD len;
    HRESULT hres;
    DWORD scheme_type;

    if(zone == URLZONE_INVALID)
        return E_INVALIDARG;

    hres = IUri_GetScheme(uri, &scheme_type);
    if(FAILED(hres))
        return hres;

    /* Windows handles opaque URLs differently then hierarchical ones. */
    if(!is_hierarchical_scheme(scheme_type) && scheme_type != URL_SCHEME_WILDCARD) {
        BSTR display_uri;

        hres = IUri_GetDisplayUri(uri, &display_uri);
        if(FAILED(hres))
            return hres;

        len = WideCharToMultiByte(CP_ACP, 0, display_uri, -1, NULL, 0, NULL, NULL)-1;

        if(len+sizeof(DWORD) > *secid_len) {
            SysFreeString(display_uri);
            return E_NOT_SUFFICIENT_BUFFER;
        }

        WideCharToMultiByte(CP_ACP, 0, display_uri, -1, (LPSTR)secid, len, NULL, NULL);
        SysFreeString(display_uri);

        *(DWORD*)(secid+len) = zone;
    } else {
        BSTR host, scheme;
        DWORD host_len, scheme_len;
        BYTE *ptr;

        hres = IUri_GetHost(uri, &host);
        if(FAILED(hres))
            return hres;

        /* The host can't be empty for Wildcard URIs. */
        if(scheme_type == URL_SCHEME_WILDCARD && !*host) {
            SysFreeString(host);
            return E_INVALIDARG;
        }

        hres = IUri_GetSchemeName(uri, &scheme);
        if(FAILED(hres)) {
            SysFreeString(host);
            return hres;
        }

        host_len = WideCharToMultiByte(CP_ACP, 0, host, -1, NULL, 0, NULL, NULL)-1;
        scheme_len = WideCharToMultiByte(CP_ACP, 0, scheme, -1, NULL, 0, NULL, NULL)-1;

        len = host_len+scheme_len+sizeof(BYTE);

        if(len+sizeof(DWORD) > *secid_len) {
            SysFreeString(host);
            SysFreeString(scheme);
            return E_NOT_SUFFICIENT_BUFFER;
        }

        WideCharToMultiByte(CP_ACP, 0, scheme, -1, (LPSTR)secid, len, NULL, NULL);
        SysFreeString(scheme);

        ptr = secid+scheme_len;
        *ptr++ = ':';

        WideCharToMultiByte(CP_ACP, 0, host, -1, (LPSTR)ptr, host_len, NULL, NULL);
        SysFreeString(host);

        ptr += host_len;

        *(DWORD*)ptr = zone;
    }

    *secid_len = len+sizeof(DWORD);

    return S_OK;
}