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
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  URLZONE_INVALID ; 
 int /*<<< orphan*/  generate_security_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_uri_to_zone (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT get_security_id_for_uri(IUri *uri, BYTE *secid, DWORD *secid_len)
{
    HRESULT hres;
    IUri *secur_uri;
    DWORD zone = URLZONE_INVALID;

    hres = map_uri_to_zone(uri, &zone, &secur_uri);
    if(FAILED(hres))
        return hres;

    hres = generate_security_id(secur_uri, secid, secid_len, zone);
    IUri_Release(secur_uri);

    return hres;
}