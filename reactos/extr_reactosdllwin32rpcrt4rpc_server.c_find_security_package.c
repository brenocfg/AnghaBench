#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_6__ {size_t wRPCID; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ SecPkgInfoW ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ EnumerateSecurityPackagesW (size_t*,TYPE_1__**) ; 
 int /*<<< orphan*/  FreeContextBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_SEC_PKG_ERROR ; 
 int /*<<< orphan*/  RPC_S_UNKNOWN_AUTHN_SERVICE ; 
 scalar_t__ SEC_E_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  WARN (char*,size_t) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RPC_STATUS find_security_package(ULONG auth_type, SecPkgInfoW **packages_buf, SecPkgInfoW **ret)
{
    SECURITY_STATUS sec_status;
    SecPkgInfoW *packages;
    ULONG package_count;
    ULONG i;

    sec_status = EnumerateSecurityPackagesW(&package_count, &packages);
    if (sec_status != SEC_E_OK)
    {
        ERR("EnumerateSecurityPackagesW failed with error 0x%08x\n", sec_status);
        return RPC_S_SEC_PKG_ERROR;
    }

    for (i = 0; i < package_count; i++)
        if (packages[i].wRPCID == auth_type)
            break;

    if (i == package_count)
    {
        WARN("unsupported AuthnSvc %u\n", auth_type);
        FreeContextBuffer(packages);
        return RPC_S_UNKNOWN_AUTHN_SERVICE;
    }

    TRACE("found package %s for service %u\n", debugstr_w(packages[i].Name), auth_type);
    *packages_buf = packages;
    *ret = packages + i;
    return RPC_S_OK;
}