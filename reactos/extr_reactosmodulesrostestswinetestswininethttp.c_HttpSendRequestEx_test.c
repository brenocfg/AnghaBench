#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szPostData ;
typedef  int /*<<< orphan*/  szContentType ;
struct TYPE_3__ {int dwStructSize; char const* lpcszHeader; int dwHeadersLength; int dwHeadersTotal; char* lpvBuffer; int dwBufferLength; int dwBufferTotal; scalar_t__ dwOffsetHigh; scalar_t__ dwOffsetLow; struct TYPE_3__* Next; } ;
typedef  TYPE_1__ INTERNET_BUFFERSA ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ CHAR ;
typedef  int /*<<< orphan*/  BufferIn ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INTERNET_NAME_NOT_RESOLVED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HttpEndRequestA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HttpOpenRequestA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HttpSendRequestExA (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNET_DEFAULT_HTTP_PORT ; 
 int /*<<< orphan*/  INTERNET_FLAG_NO_CACHE_WRITE ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_PRECONFIG ; 
 int /*<<< orphan*/  INTERNET_REQFLAG_NO_HEADERS ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetConnectA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InternetReadFile (int /*<<< orphan*/ *,scalar_t__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  InternetWriteFile (int /*<<< orphan*/ *,char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  proxy_active () ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ strncmp (scalar_t__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_request_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void HttpSendRequestEx_test(void)
{
    HINTERNET hSession;
    HINTERNET hConnect;
    HINTERNET hRequest;

    INTERNET_BUFFERSA BufferIn;
    DWORD dwBytesWritten, dwBytesRead, error;
    CHAR szBuffer[256];
    int i;
    BOOL ret;

    static char szPostData[] = "mode=Test";
    static const char szContentType[] = "Content-Type: application/x-www-form-urlencoded";

    hSession = InternetOpenA("Wine Regression Test",
            INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
    ok( hSession != NULL ,"Unable to open Internet session\n");
    hConnect = InternetConnectA(hSession, "test.winehq.org",
            INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0,
            0);
    ok( hConnect != NULL, "Unable to connect to http://test.winehq.org\n");
    hRequest = HttpOpenRequestA(hConnect, "POST", "/tests/post.php",
            NULL, NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE, 0);
    if (!hRequest && GetLastError() == ERROR_INTERNET_NAME_NOT_RESOLVED)
    {
        skip( "Network unreachable, skipping test\n" );
        goto done;
    }
    ok( hRequest != NULL, "Failed to open request handle err %u\n", GetLastError());

    test_request_flags(hRequest, INTERNET_REQFLAG_NO_HEADERS);

    BufferIn.dwStructSize = sizeof(BufferIn);
    BufferIn.Next = (INTERNET_BUFFERSA*)0xdeadcab;
    BufferIn.lpcszHeader = szContentType;
    BufferIn.dwHeadersLength = sizeof(szContentType)-1;
    BufferIn.dwHeadersTotal = sizeof(szContentType)-1;
    BufferIn.lpvBuffer = szPostData;
    BufferIn.dwBufferLength = 3;
    BufferIn.dwBufferTotal = sizeof(szPostData)-1;
    BufferIn.dwOffsetLow = 0;
    BufferIn.dwOffsetHigh = 0;

    SetLastError(0xdeadbeef);
    ret = HttpSendRequestExA(hRequest, &BufferIn, NULL, 0 ,0);
    error = GetLastError();
    ok(ret, "HttpSendRequestEx Failed with error %u\n", error);
    ok(error == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %u\n", error);

    test_request_flags(hRequest, INTERNET_REQFLAG_NO_HEADERS);

    for (i = 3; szPostData[i]; i++)
        ok(InternetWriteFile(hRequest, &szPostData[i], 1, &dwBytesWritten),
                "InternetWriteFile failed\n");

    test_request_flags(hRequest, INTERNET_REQFLAG_NO_HEADERS);

    ok(HttpEndRequestA(hRequest, NULL, 0, 0), "HttpEndRequest Failed\n");

    test_request_flags(hRequest, 0);

    ok(InternetReadFile(hRequest, szBuffer, 255, &dwBytesRead),
            "Unable to read response\n");
    szBuffer[dwBytesRead] = 0;

    ok(dwBytesRead == 13,"Read %u bytes instead of 13\n",dwBytesRead);
    ok(strncmp(szBuffer,"mode => Test\n",dwBytesRead)==0 || broken(proxy_active()),"Got string %s\n",szBuffer);

    ok(InternetCloseHandle(hRequest), "Close request handle failed\n");
done:
    ok(InternetCloseHandle(hConnect), "Close connect handle failed\n");
    ok(InternetCloseHandle(hSession), "Close session handle failed\n");
}