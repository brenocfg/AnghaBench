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
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int DnsFlushResolverCacheEntry_A (char*) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_DnsFlushResolverCacheEntry_A(void)
{
    BOOL ret;
    DWORD err;

    SetLastError( 0xdeadbeef );
    ret = DnsFlushResolverCacheEntry_A( NULL );
    err = GetLastError();
    ok( !ret, "got %d\n", ret );
    ok( err == 0xdeadbeef, "got %u\n", err );

    ret = DnsFlushResolverCacheEntry_A( "localhost" );
    ok( ret, "got %d\n", ret );

    ret = DnsFlushResolverCacheEntry_A( "nxdomain.test.winehq.org" );
    ok( ret, "got %d\n", ret );
}