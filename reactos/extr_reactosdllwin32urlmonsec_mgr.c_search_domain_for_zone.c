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
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 
 int /*<<< orphan*/  find_domain_name (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ get_zone_for_scheme (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/ * heap_alloc (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_strndupW (scalar_t__,scalar_t__) ; 
 scalar_t__ matches_domain_pattern (scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  strchrW (scalar_t__,scalar_t__) ; 

__attribute__((used)) static HRESULT search_domain_for_zone(HKEY domains, LPCWSTR domain, DWORD domain_len, LPCWSTR schema,
                                      LPCWSTR host, DWORD host_len, DWORD *zone)
{
    BOOL found = FALSE;
    HKEY domain_key;
    DWORD res;
    LPCWSTR matched;

    if(host_len >= domain_len && matches_domain_pattern(domain, host, TRUE, &matched)) {
        res = RegOpenKeyW(domains, domain, &domain_key);
        if(res != ERROR_SUCCESS) {
            ERR("Failed to open domain key %s: %d\n", debugstr_w(domain), res);
            return E_UNEXPECTED;
        }

        if(matched == host)
            found = get_zone_for_scheme(domain_key, schema, zone);
        else {
            INT domain_offset;
            DWORD subdomain_count, subdomain_len;
            BOOL check_domain = TRUE;

            find_domain_name(domain, domain_len, &domain_offset);

            res = RegQueryInfoKeyW(domain_key, NULL, NULL, NULL, &subdomain_count, &subdomain_len,
                                   NULL, NULL, NULL, NULL, NULL, NULL);
            if(res != ERROR_SUCCESS) {
                ERR("Unable to query info for key %s: %d\n", debugstr_w(domain), res);
                RegCloseKey(domain_key);
                return E_UNEXPECTED;
            }

            if(subdomain_count) {
                WCHAR *subdomain;
                WCHAR *component;
                DWORD i;

                subdomain = heap_alloc((subdomain_len+1)*sizeof(WCHAR));
                if(!subdomain) {
                    RegCloseKey(domain_key);
                    return E_OUTOFMEMORY;
                }

                component = heap_strndupW(host, matched-host-1);
                if(!component) {
                    heap_free(subdomain);
                    RegCloseKey(domain_key);
                    return E_OUTOFMEMORY;
                }

                for(i = 0; i < subdomain_count; ++i) {
                    DWORD len = subdomain_len+1;
                    const WCHAR *sub_matched;

                    res = RegEnumKeyExW(domain_key, i, subdomain, &len, NULL, NULL, NULL, NULL);
                    if(res != ERROR_SUCCESS) {
                        heap_free(component);
                        heap_free(subdomain);
                        RegCloseKey(domain_key);
                        return E_UNEXPECTED;
                    }

                    if(matches_domain_pattern(subdomain, component, FALSE, &sub_matched)) {
                        HKEY subdomain_key;

                        res = RegOpenKeyW(domain_key, subdomain, &subdomain_key);
                        if(res != ERROR_SUCCESS) {
                            ERR("Unable to open subdomain key %s of %s: %d\n", debugstr_w(subdomain),
                                debugstr_w(domain), res);
                            heap_free(component);
                            heap_free(subdomain);
                            RegCloseKey(domain_key);
                            return E_UNEXPECTED;
                        }

                        found = get_zone_for_scheme(subdomain_key, schema, zone);
                        check_domain = FALSE;
                        RegCloseKey(subdomain_key);
                        break;
                    }
                }
                heap_free(subdomain);
                heap_free(component);
            }

            /* There's a chance that 'host' implicitly mapped into 'domain', in
             * which case we check to see if 'domain' contains zone information.
             *
             * This can only happen if 'domain' is its own domain name.
             *  Example:
             *      "google.com" (domain name = "google.com")
             *
             *  So if:
             *      host = "www.google.com"
             *
             *  Then host would map directly into the "google.com" domain key.
             *
             * If 'domain' has more than just its domain name, or it does not
             * have a domain name, then we don't perform the check. The reason
             * for this is that these domains don't allow implicit mappings.
             *  Example:
             *      domain = "org" (has no domain name)
             *      host   = "www.org"
             *
             *  The mapping would only happen if the "org" key had an explicit subkey
             *  called "www".
             */
            if(check_domain && !domain_offset && !strchrW(host, matched-host-1))
                found = get_zone_for_scheme(domain_key, schema, zone);
        }
        RegCloseKey(domain_key);
    }

    return found ? S_OK : S_FALSE;
}