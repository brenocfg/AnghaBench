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
typedef  int /*<<< orphan*/  status ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int GetLastError () ; 
 int HTTP_QUERY_FLAG_NUMBER ; 
 int HTTP_QUERY_STATUS_CODE ; 
 int /*<<< orphan*/ * HttpOpenRequestA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HttpQueryInfoA (int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ *) ; 
 int HttpSendRequestA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_DIRECT ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetConnectA (int /*<<< orphan*/ *,char*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_basic_auth_credentials_reuse(int port)
{
    HINTERNET ses, con, req;
    DWORD status, size;
    BOOL ret;

    ses = InternetOpenA( "winetest", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0 );
    ok( ses != NULL, "InternetOpenA failed\n" );

    con = InternetConnectA( ses, "localhost", port, "user", "pwd",
                            INTERNET_SERVICE_HTTP, 0, 0 );
    ok( con != NULL, "InternetConnectA failed %u\n", GetLastError() );

    req = HttpOpenRequestA( con, "HEAD", "/upload.txt", NULL, NULL, NULL, 0, 0 );
    ok( req != NULL, "HttpOpenRequestA failed %u\n", GetLastError() );

    ret = HttpSendRequestA( req, NULL, 0, NULL, 0 );
    ok( ret, "HttpSendRequestA failed %u\n", GetLastError() );

    status = 0xdeadbeef;
    size = sizeof(status);
    ret = HttpQueryInfoA( req, HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, &status, &size, NULL );
    ok( ret, "HttpQueryInfoA failed %u\n", GetLastError() );
    ok( status == 200, "got %u\n", status );

    InternetCloseHandle( req );
    InternetCloseHandle( con );
    InternetCloseHandle( ses );

    ses = InternetOpenA( "winetest", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0 );
    ok( ses != NULL, "InternetOpenA failed\n" );

    con = InternetConnectA( ses, "localhost", port, NULL, NULL,
                            INTERNET_SERVICE_HTTP, 0, 0 );
    ok( con != NULL, "InternetConnectA failed %u\n", GetLastError() );

    req = HttpOpenRequestA( con, "PUT", "/upload2.txt", NULL, NULL, NULL, 0, 0 );
    ok( req != NULL, "HttpOpenRequestA failed %u\n", GetLastError() );

    ret = HttpSendRequestA( req, NULL, 0, NULL, 0 );
    ok( ret, "HttpSendRequestA failed %u\n", GetLastError() );

    status = 0xdeadbeef;
    size = sizeof(status);
    ret = HttpQueryInfoA( req, HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, &status, &size, NULL );
    ok( ret, "HttpQueryInfoA failed %u\n", GetLastError() );
    ok( status == 200, "got %u\n", status );

    InternetCloseHandle( req );
    InternetCloseHandle( con );
    InternetCloseHandle( ses );
}