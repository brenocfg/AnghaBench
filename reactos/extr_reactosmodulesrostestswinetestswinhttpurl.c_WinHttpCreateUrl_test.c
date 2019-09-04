#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
struct TYPE_5__ {unsigned int dwSchemeLength; int nPort; unsigned int dwExtraInfoLength; scalar_t__ nScheme; int /*<<< orphan*/ * lpszScheme; int /*<<< orphan*/ * lpszExtraInfo; int /*<<< orphan*/ * lpszPassword; int /*<<< orphan*/ * lpszUserName; } ;
typedef  TYPE_1__ URL_COMPONENTS ;
typedef  unsigned int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 unsigned int ERROR_INSUFFICIENT_BUFFER ; 
 unsigned int ERROR_INVALID_PARAMETER ; 
 unsigned int ERROR_SUCCESS ; 
 unsigned int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ICU_ESCAPE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int WinHttpCreateUrl (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,unsigned int*) ; 
 scalar_t__ broken (int) ; 
 void* empty ; 
 int /*<<< orphan*/ * escape ; 
 int /*<<< orphan*/  fill_url_components (TYPE_1__*) ; 
 int /*<<< orphan*/ * ftp ; 
 int /*<<< orphan*/ * http ; 
 int /*<<< orphan*/  lstrcmpW (scalar_t__*,int /*<<< orphan*/ *) ; 
 unsigned int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * url1 ; 
 int /*<<< orphan*/ * url2 ; 
 int /*<<< orphan*/ * url3 ; 
 int /*<<< orphan*/ * url4 ; 
 int /*<<< orphan*/ * url5 ; 
 int /*<<< orphan*/ * url6 ; 
 int /*<<< orphan*/ * url7 ; 
 int /*<<< orphan*/ * url8 ; 

__attribute__((used)) static void WinHttpCreateUrl_test( void )
{
    URL_COMPONENTS uc;
    WCHAR *url;
    DWORD len, err;
    BOOL ret;

    /* NULL components */
    len = ~0u;
    SetLastError( 0xdeadbeef );
    ret = WinHttpCreateUrl( NULL, 0, NULL, &len );
    ok( !ret, "expected failure\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got %u\n", GetLastError() );
    ok( len == ~0u, "expected len ~0u got %u\n", len );

    /* zero'ed components */
    memset( &uc, 0, sizeof(URL_COMPONENTS) );
    SetLastError( 0xdeadbeef );
    ret = WinHttpCreateUrl( &uc, 0, NULL, &len );
    ok( !ret, "expected failure\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got %u\n", GetLastError() );
    ok( len == ~0u, "expected len ~0u got %u\n", len );

    /* valid components, NULL url, NULL length */
    fill_url_components( &uc );
    SetLastError( 0xdeadbeef );
    ret = WinHttpCreateUrl( &uc, 0, NULL, NULL );
    ok( !ret, "expected failure\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got %u\n", GetLastError() );

    /* valid components, NULL url, insufficient length */
    len = 0;
    SetLastError( 0xdeadbeef );
    ret = WinHttpCreateUrl( &uc, 0, NULL, &len );
    ok( !ret, "expected failure\n" );
    ok( GetLastError() == ERROR_INSUFFICIENT_BUFFER, "expected ERROR_INSUFFICIENT_BUFFER got %u\n", GetLastError() );
    ok( len == 57, "expected len 57 got %u\n", len );

    /* valid components, NULL url, sufficient length */
    SetLastError( 0xdeadbeef );
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, NULL, &len );
    err = GetLastError();
    ok( !ret, "expected failure\n" );
    ok( err == ERROR_INVALID_PARAMETER || broken(err == ERROR_INSUFFICIENT_BUFFER) /* < win7 */,
        "expected ERROR_INVALID_PARAMETER got %u\n", GetLastError() );
    ok( len == 256 || broken(len == 57) /* < win7 */, "expected len 256 got %u\n", len );

    /* correct size, NULL url */
    fill_url_components( &uc );
    SetLastError( 0xdeadbeef );
    ret = WinHttpCreateUrl( &uc, 0, NULL, &len );
    err = GetLastError();
    ok( !ret, "expected failure\n" );
    ok( err == ERROR_INVALID_PARAMETER || broken(err == ERROR_INSUFFICIENT_BUFFER) /* < win7 */,
        "expected ERROR_INVALID_PARAMETER got %u\n", GetLastError() );
    ok( len == 256 || broken(len == 57) /* < win7 */, "expected len 256 got %u\n", len );

    /* valid components, allocated url, short length */
    SetLastError( 0xdeadbeef );
    url = HeapAlloc( GetProcessHeap(), 0, 256 * sizeof(WCHAR) );
    url[0] = 0;
    len = 2;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( !ret, "expected failure\n" );
    ok( GetLastError() == ERROR_INSUFFICIENT_BUFFER, "expected ERROR_INSUFFICIENT_BUFFER got %u\n", GetLastError() );
    ok( len == 57, "expected len 57 got %u\n", len );

    /* allocated url, NULL scheme */
    SetLastError( 0xdeadbeef );
    uc.lpszScheme = NULL;
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n" );
    ok( GetLastError() == ERROR_SUCCESS || broken(GetLastError() == 0xdeadbeef) /* < win7 */,
        "expected ERROR_SUCCESS got %u\n", GetLastError() );
    ok( len == 56, "expected len 56 got %u\n", len );
    ok( !lstrcmpW( url, url1 ), "url doesn't match\n" );

    /* allocated url, 0 scheme */
    fill_url_components( &uc );
    uc.nScheme = 0;
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n" );
    ok( len == 56, "expected len 56 got %u\n", len );

    /* valid components, allocated url */
    fill_url_components( &uc );
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n" );
    ok( len == 56, "expected len 56 got %d\n", len );
    ok( !lstrcmpW( url, url1 ), "url doesn't match\n" );

    /* valid username, NULL password */
    fill_url_components( &uc );
    uc.lpszPassword = NULL;
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n" );

    /* valid username, empty password */
    fill_url_components( &uc );
    uc.lpszPassword = empty;
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n" );
    ok( len == 56, "expected len 56 got %u\n", len );
    ok( !lstrcmpW( url, url2 ), "url doesn't match\n" );

    /* valid password, NULL username */
    fill_url_components( &uc );
    SetLastError( 0xdeadbeef );
    uc.lpszUserName = NULL;
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( !ret, "expected failure\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER got %u\n", GetLastError() );

    /* valid password, empty username */
    fill_url_components( &uc );
    uc.lpszUserName = empty;
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n");

    /* NULL username, NULL password */
    fill_url_components( &uc );
    uc.lpszUserName = NULL;
    uc.lpszPassword = NULL;
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n" );
    ok( len == 38, "expected len 38 got %u\n", len );
    ok( !lstrcmpW( url, url3 ), "url doesn't match\n" );

    /* empty username, empty password */
    fill_url_components( &uc );
    uc.lpszUserName = empty;
    uc.lpszPassword = empty;
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n" );
    ok( len == 56, "expected len 56 got %u\n", len );
    ok( !lstrcmpW( url, url4 ), "url doesn't match\n" );

    /* nScheme has lower precedence than lpszScheme */
    fill_url_components( &uc );
    uc.lpszScheme = ftp;
    uc.dwSchemeLength = lstrlenW( uc.lpszScheme );
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n" );
    ok( len == lstrlenW( url5 ), "expected len %d got %u\n", lstrlenW( url5 ) + 1, len );
    ok( !lstrcmpW( url, url5 ), "url doesn't match\n" );

    /* non-standard port */
    uc.lpszScheme = http;
    uc.dwSchemeLength = lstrlenW( uc.lpszScheme );
    uc.nPort = 42;
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n" );
    ok( len == 59, "expected len 59 got %u\n", len );
    ok( !lstrcmpW( url, url6 ), "url doesn't match\n" );

    /* escape extra info */
    fill_url_components( &uc );
    uc.lpszExtraInfo = escape;
    uc.dwExtraInfoLength = lstrlenW( uc.lpszExtraInfo );
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, ICU_ESCAPE, url, &len );
    ok( ret, "expected success\n" );
    ok( len == 113, "expected len 113 got %u\n", len );
    ok( !lstrcmpW( url, url7 ), "url doesn't match\n" );

    /* NULL lpszScheme, 0 nScheme and nPort */
    fill_url_components( &uc );
    uc.lpszScheme = NULL;
    uc.dwSchemeLength = 0;
    uc.nScheme = 0;
    uc.nPort = 0;
    url[0] = 0;
    len = 256;
    ret = WinHttpCreateUrl( &uc, 0, url, &len );
    ok( ret, "expected success\n" );
    ok( len == 58, "expected len 58 got %u\n", len );
    ok( !lstrcmpW( url, url8 ), "url doesn't match\n" );

    HeapFree( GetProcessHeap(), 0, url );
}