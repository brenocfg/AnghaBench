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
typedef  int /*<<< orphan*/  SspiData ;
typedef  int /*<<< orphan*/  SecPkgInfoA ;
typedef  int /*<<< orphan*/  SEC_CHAR ;
typedef  scalar_t__ SECURITY_STATUS ;

/* Variables and functions */
 scalar_t__ SEC_E_OK ; 
 int /*<<< orphan*/  getSecError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pFreeContextBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ pQuerySecurityPackageInfoA (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ setupBuffers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static SECURITY_STATUS setupFakeServer(SspiData *sspi_data, SEC_CHAR *provider)
{
    SECURITY_STATUS ret;
    SecPkgInfoA *sec_pkg_info;

    trace("Running setupFakeServer\n");

    ret = pQuerySecurityPackageInfoA(provider, &sec_pkg_info);

    ok(ret == SEC_E_OK, "QuerySecurityPackageInfo returned %s\n", getSecError(ret));

    ret = setupBuffers(sspi_data, sec_pkg_info);
    pFreeContextBuffer(sec_pkg_info);
    
    return ret;
}