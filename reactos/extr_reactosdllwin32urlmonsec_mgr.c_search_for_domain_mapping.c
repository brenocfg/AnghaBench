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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/ * heap_alloc (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  search_domain_for_zone (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static HRESULT search_for_domain_mapping(HKEY domains, LPCWSTR schema, LPCWSTR host, DWORD host_len, DWORD *zone)
{
    WCHAR *domain;
    DWORD domain_count, domain_len, i;
    DWORD res;
    HRESULT hres = S_FALSE;

    res = RegQueryInfoKeyW(domains, NULL, NULL, NULL, &domain_count, &domain_len,
                           NULL, NULL, NULL, NULL, NULL, NULL);
    if(res != ERROR_SUCCESS) {
        WARN("Failed to retrieve information about key\n");
        return E_UNEXPECTED;
    }

    if(!domain_count)
        return S_FALSE;

    domain = heap_alloc((domain_len+1)*sizeof(WCHAR));
    if(!domain)
        return E_OUTOFMEMORY;

    for(i = 0; i < domain_count; ++i) {
        DWORD len = domain_len+1;

        res = RegEnumKeyExW(domains, i, domain, &len, NULL, NULL, NULL, NULL);
        if(res != ERROR_SUCCESS) {
            heap_free(domain);
            return E_UNEXPECTED;
        }

        hres = search_domain_for_zone(domains, domain, len, schema, host, host_len, zone);
        if(FAILED(hres) || hres == S_OK)
            break;
    }

    heap_free(domain);
    return hres;
}