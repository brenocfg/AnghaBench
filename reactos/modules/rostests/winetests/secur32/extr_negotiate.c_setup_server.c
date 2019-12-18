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
struct sspi_data {int /*<<< orphan*/  cred; } ;
typedef  int /*<<< orphan*/  TimeStamp ;
typedef  int /*<<< orphan*/  SecPkgInfoA ;
typedef  int /*<<< orphan*/  SEC_CHAR ;
typedef  scalar_t__ SECURITY_STATUS ;

/* Variables and functions */
 scalar_t__ AcquireCredentialsHandleA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeContextBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ QuerySecurityPackageInfoA (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SECPKG_CRED_INBOUND ; 
 scalar_t__ SEC_E_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  setup_buffers (struct sspi_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static SECURITY_STATUS setup_server( struct sspi_data *data, SEC_CHAR *provider )
{
    SECURITY_STATUS ret;
    SecPkgInfoA *info;
    TimeStamp ttl;

    trace( "setting up server\n" );

    ret = QuerySecurityPackageInfoA( provider, &info );
    ok( ret == SEC_E_OK, "QuerySecurityPackageInfo returned %08x\n", ret );

    setup_buffers( data, info );
    FreeContextBuffer( info );

    ret = AcquireCredentialsHandleA( NULL, provider, SECPKG_CRED_INBOUND, NULL,
                                     NULL, NULL, NULL, &data->cred, &ttl );
    ok( ret == SEC_E_OK, "AcquireCredentialsHandleA returned %08x\n", ret );
    return ret;
}