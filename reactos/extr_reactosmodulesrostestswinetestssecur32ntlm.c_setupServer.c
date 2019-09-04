#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TimeStamp ;
struct TYPE_4__ {int /*<<< orphan*/  cred; } ;
typedef  TYPE_1__ SspiData ;
typedef  int /*<<< orphan*/  SecPkgInfoA ;
typedef  int /*<<< orphan*/  SEC_CHAR ;
typedef  scalar_t__ SECURITY_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SECPKG_CRED_INBOUND ; 
 scalar_t__ SEC_E_OK ; 
 int /*<<< orphan*/  getSecError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pAcquireCredentialsHandleA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFreeContextBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ pQuerySecurityPackageInfoA (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  setupBuffers (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static SECURITY_STATUS setupServer(SspiData *sspi_data, SEC_CHAR *provider)
{
    SECURITY_STATUS ret;
    TimeStamp ttl;
    SecPkgInfoA *sec_pkg_info;

    trace("Running setupServer\n");

    ret = pQuerySecurityPackageInfoA(provider, &sec_pkg_info);

    ok(ret == SEC_E_OK, "QuerySecurityPackageInfo returned %s\n", getSecError(ret));

    setupBuffers(sspi_data, sec_pkg_info);
    pFreeContextBuffer(sec_pkg_info);

    if((ret = pAcquireCredentialsHandleA(NULL, provider, SECPKG_CRED_INBOUND, 
            NULL, NULL, NULL, NULL, &sspi_data->cred, &ttl)) != SEC_E_OK)
    {
        trace("AcquireCredentialsHandle() returned %s\n", getSecError(ret));
    }

    ok(ret == SEC_E_OK, "AcquireCredentialsHandle() returned %s\n",
            getSecError(ret));

    return ret;
}