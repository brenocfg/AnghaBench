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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IInternetProtocolInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IInternetProtocolInfo_ParseUrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PARSE_CANONICALIZE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UrlCanonicalizeW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_protocol_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT parse_canonicalize_url(LPCWSTR url, DWORD flags, LPWSTR result,
        DWORD size, DWORD *rsize)
{
    IInternetProtocolInfo *protocol_info;
    DWORD prsize = size;
    HRESULT hres;

    TRACE("(%s %08x %p %d %p)\n", debugstr_w(url), flags, result, size, rsize);

    protocol_info = get_protocol_info(url);

    if(protocol_info) {
        hres = IInternetProtocolInfo_ParseUrl(protocol_info, url, PARSE_CANONICALIZE,
                flags, result, size, rsize, 0);
        IInternetProtocolInfo_Release(protocol_info);
        if(SUCCEEDED(hres))
            return hres;
    }

    hres = UrlCanonicalizeW(url, result, &prsize, flags);

    if(rsize)
        *rsize = prsize;
    return hres;
}