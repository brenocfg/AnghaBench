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
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CoInternetGetSecurityUrlEx (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PSU_SECURITY_URL_ONLY ; 
 int /*<<< orphan*/  map_security_uri_to_zone (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT map_uri_to_zone(IUri *uri, DWORD *zone, IUri **ret_uri)
{
    HRESULT hres;
    IUri *secur_uri;

    hres = CoInternetGetSecurityUrlEx(uri, &secur_uri, PSU_SECURITY_URL_ONLY, 0);
    if(FAILED(hres))
        return hres;

    hres = map_security_uri_to_zone(secur_uri, zone);
    if(FAILED(hres) || !ret_uri)
        IUri_Release(secur_uri);
    else
        *ret_uri = secur_uri;

    return hres;
}