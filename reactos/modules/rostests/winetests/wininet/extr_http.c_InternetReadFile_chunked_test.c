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
typedef  int HINTERNET ;
typedef  size_t DWORD ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_HTTP_HEADER_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_INTERNET_NAME_NOT_RESOLVED ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HTTP_QUERY_CONTENT_LENGTH ; 
 int /*<<< orphan*/  HTTP_QUERY_CONTENT_TYPE ; 
 int /*<<< orphan*/  HTTP_QUERY_TRANSFER_ENCODING ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int HttpOpenRequestA (int,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int,int) ; 
 int HttpQueryInfoA (int,int /*<<< orphan*/ ,...) ; 
 int HttpSendRequestA (int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INTERNET_FLAG_KEEP_CONNECTION ; 
 int INTERNET_FLAG_RELOAD ; 
 int /*<<< orphan*/  INTERNET_INVALID_PORT_NUMBER ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_PRECONFIG ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 int InternetCloseHandle (int) ; 
 int InternetConnectA (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int InternetOpenA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int InternetQueryDataAvailable (int,size_t*,int,int) ; 
 int InternetReadFile (int,char*,int,size_t*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ proxy_active () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_request_flags (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void InternetReadFile_chunked_test(void)
{
    BOOL res;
    CHAR buffer[4000];
    DWORD length, got;
    const char *types[2] = { "*", NULL };
    HINTERNET hi, hic = 0, hor = 0;

    trace("Starting InternetReadFile chunked test\n");

    trace("InternetOpenA <--\n");
    hi = InternetOpenA("", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    ok((hi != 0x0),"InternetOpen failed with error %u\n", GetLastError());
    trace("InternetOpenA -->\n");

    if (hi == 0x0) goto abort;

    trace("InternetConnectA <--\n");
    hic=InternetConnectA(hi, "test.winehq.org", INTERNET_INVALID_PORT_NUMBER,
                         NULL, NULL, INTERNET_SERVICE_HTTP, 0x0, 0xdeadbeef);
    ok((hic != 0x0),"InternetConnect failed with error %u\n", GetLastError());
    trace("InternetConnectA -->\n");

    if (hic == 0x0) goto abort;

    trace("HttpOpenRequestA <--\n");
    hor = HttpOpenRequestA(hic, "GET", "/tests/chunked", NULL, NULL, types,
                           INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_RELOAD,
                           0xdeadbead);
    if (hor == 0x0 && GetLastError() == ERROR_INTERNET_NAME_NOT_RESOLVED) {
        /*
         * If the internet name can't be resolved we are probably behind
         * a firewall or in some other way not directly connected to the
         * Internet. Not enough reason to fail the test. Just ignore and
         * abort.
         */
    } else  {
        ok((hor != 0x0),"HttpOpenRequest failed with error %u\n", GetLastError());
    }
    trace("HttpOpenRequestA -->\n");

    if (hor == 0x0) goto abort;

    trace("HttpSendRequestA -->\n");
    SetLastError(0xdeadbeef);
    res = HttpSendRequestA(hor, "", -1, NULL, 0);
    ok(res || (GetLastError() == ERROR_INTERNET_NAME_NOT_RESOLVED),
       "Synchronous HttpSendRequest returning 0, error %u\n", GetLastError());
    trace("HttpSendRequestA <--\n");

    test_request_flags(hor, 0);

    length = 100;
    res = HttpQueryInfoA(hor,HTTP_QUERY_CONTENT_TYPE,buffer,&length,0x0);
    buffer[length]=0;
    trace("Option CONTENT_TYPE -> %i  %s\n",res,buffer);

    SetLastError( 0xdeadbeef );
    length = 100;
    res = HttpQueryInfoA(hor,HTTP_QUERY_TRANSFER_ENCODING,buffer,&length,0x0);
    buffer[length]=0;
    trace("Option TRANSFER_ENCODING -> %i  %s\n",res,buffer);
    ok( res || ( proxy_active() && GetLastError() == ERROR_HTTP_HEADER_NOT_FOUND ),
        "Failed to get TRANSFER_ENCODING option, error %u\n", GetLastError() );
    ok( !strcmp( buffer, "chunked" ) || ( ! res && proxy_active() && GetLastError() == ERROR_HTTP_HEADER_NOT_FOUND ),
        "Wrong transfer encoding '%s'\n", buffer );

    SetLastError( 0xdeadbeef );
    length = 16;
    res = HttpQueryInfoA(hor,HTTP_QUERY_CONTENT_LENGTH,&buffer,&length,0x0);
    ok( !res, "Found CONTENT_LENGTH option '%s'\n", buffer );
    ok( GetLastError() == ERROR_HTTP_HEADER_NOT_FOUND, "Wrong error %u\n", GetLastError() );

    length = 100;
    trace("Entering Query loop\n");

    while (TRUE)
    {
        res = InternetQueryDataAvailable(hor,&length,0x0,0x0);
        ok(!(!res && length != 0),"InternetQueryDataAvailable failed with non-zero length\n");
        ok(res, "InternetQueryDataAvailable failed, error %d\n", GetLastError());
        trace("got %u available\n",length);
        if (length)
        {
            char *buffer = HeapAlloc(GetProcessHeap(),0,length+1);

            res = InternetReadFile(hor,buffer,length,&got);

            buffer[got]=0;
            trace("ReadFile -> %i %i\n",res,got);
            ok( length == got, "only got %u of %u available\n", got, length );
            ok( buffer[got-1] == '\n', "received partial line '%s'\n", buffer );

            HeapFree(GetProcessHeap(),0,buffer);
            if (!got) break;
        }
        if (length == 0)
        {
            got = 0xdeadbeef;
            res = InternetReadFile( hor, buffer, 1, &got );
            ok( res, "InternetReadFile failed: %u\n", GetLastError() );
            ok( !got, "got %u\n", got );
            break;
        }
    }
abort:
    trace("aborting\n");
    if (hor != 0x0) {
        res = InternetCloseHandle(hor);
        ok (res, "InternetCloseHandle of handle opened by HttpOpenRequestA failed\n");
    }
    if (hi != 0x0) {
        res = InternetCloseHandle(hi);
        ok (res, "InternetCloseHandle of handle opened by InternetOpenA failed\n");
    }
}