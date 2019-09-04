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
typedef  int /*<<< orphan*/  SEC_CHAR ;
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  int /*<<< orphan*/  PSecPkgInfoA ;

/* Variables and functions */
 int /*<<< orphan*/  pQuerySecurityPackageInfoA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SECURITY_STATUS setupPackageA(SEC_CHAR *p_package_name, 
        PSecPkgInfoA *p_pkg_info)
{
    SECURITY_STATUS ret;
    
    ret = pQuerySecurityPackageInfoA( p_package_name, p_pkg_info);
    return ret;
}