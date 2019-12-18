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
typedef  char WCHAR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char*) ; 
 scalar_t__ DsClientMakeSpnForTargetServerW (char const*,char const*,scalar_t__*,char*) ; 
 scalar_t__ ERROR_BUFFER_OVERFLOW ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 scalar_t__ lstrlenW (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_DsClientMakeSpnForTargetServer(void)
{
    static const WCHAR classW[] = {'c','l','a','s','s',0};
    static const WCHAR hostW[] = {'h','o','s','t','.','d','o','m','a','i','n',0};
    static const WCHAR resultW[] = {'c','l','a','s','s','/','h','o','s','t','.','d','o','m','a','i','n',0};
    DWORD ret, len;
    WCHAR buf[256];

    ret = DsClientMakeSpnForTargetServerW( NULL, NULL, NULL, NULL );
    ok( ret == ERROR_INVALID_PARAMETER, "got %u\n", ret );

    ret = DsClientMakeSpnForTargetServerW( classW, NULL, NULL, NULL );
    ok( ret == ERROR_INVALID_PARAMETER, "got %u\n", ret );

    ret = DsClientMakeSpnForTargetServerW( classW, hostW, NULL, NULL );
    ok( ret == ERROR_INVALID_PARAMETER, "got %u\n", ret );

    len = 0;
    ret = DsClientMakeSpnForTargetServerW( classW, hostW, &len, NULL );
    ok( ret == ERROR_BUFFER_OVERFLOW, "got %u\n", ret );
    ok( len == lstrlenW(resultW) + 1, "got %u\n", len );

    len = ARRAY_SIZE(buf);
    buf[0] = 0;
    ret = DsClientMakeSpnForTargetServerW( classW, hostW, &len, buf );
    ok( ret == ERROR_SUCCESS, "got %u\n", ret );
    ok( len == lstrlenW(resultW) + 1, "got %u\n", len );
    ok( !lstrcmpW( buf, resultW ), "wrong data\n" );
}