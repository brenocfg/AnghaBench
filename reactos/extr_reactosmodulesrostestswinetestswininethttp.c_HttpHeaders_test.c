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
typedef  int /*<<< orphan*/  wbuffer ;
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int DWORD ;
typedef  scalar_t__ CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_HTTP_HEADER_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INTERNET_NAME_NOT_RESOLVED ; 
 int FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int HTTP_ADDREQ_FLAG_ADD ; 
 int HTTP_ADDREQ_FLAG_ADD_IF_NEW ; 
 int HTTP_ADDREQ_FLAG_COALESCE ; 
 int HTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA ; 
 int HTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON ; 
 int HTTP_ADDREQ_FLAG_REPLACE ; 
 int HTTP_QUERY_AUTHORIZATION ; 
 int HTTP_QUERY_CUSTOM ; 
 int HTTP_QUERY_FLAG_REQUEST_HEADERS ; 
 int HTTP_QUERY_RAW_HEADERS_CRLF ; 
 int HttpAddRequestHeadersA (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/ * HttpOpenRequestA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HttpQueryInfoA (int /*<<< orphan*/ *,int,scalar_t__*,int*,int*) ; 
 int HttpQueryInfoW (int /*<<< orphan*/ *,int,scalar_t__*,int*,int*) ; 
 int /*<<< orphan*/  INTERNET_DEFAULT_HTTP_PORT ; 
 int /*<<< orphan*/  INTERNET_FLAG_NO_CACHE_WRITE ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_PRECONFIG ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 int InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetConnectA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TRUE ; 
 int lstrlenW (scalar_t__*) ; 
 scalar_t__ memcmp (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ strcmp (scalar_t__*,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char*) ; 
 int strlen (scalar_t__*) ; 
 scalar_t__ strncmp (scalar_t__*,char*,int) ; 

__attribute__((used)) static void HttpHeaders_test(void)
{
    HINTERNET hSession;
    HINTERNET hConnect;
    HINTERNET hRequest;
    CHAR      buffer[256];
    WCHAR     wbuffer[256];
    DWORD     len = 256;
    DWORD     oldlen;
    DWORD     index = 0;
    BOOL      ret;

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
    ok( hRequest != NULL, "Failed to open request handle\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
               buffer,&len,&index)==0,"Warning hearder reported as Existing\n");

    ok(HttpAddRequestHeadersA(hRequest,"Warning:test1",-1,HTTP_ADDREQ_FLAG_ADD),
            "Failed to add new header\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"test1")==0, "incorrect string was returned(%s)\n",buffer);
    ok(len == 5, "Invalid length (exp. 5, got %d)\n", len);
    ok((len < sizeof(buffer)) && (buffer[len] == 0), "Buffer not NULL-terminated\n"); /* len show only 5 characters but the buffer is NULL-terminated*/
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index)==0,"Second Index Should Not Exist\n");

    index = 0;
    len = 5; /* could store the string but not the NULL terminator */
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index) == FALSE,"Query succeeded on a too small buffer\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Unexpected last error: %d\n", GetLastError());
    ok(index == 0, "Index was incremented\n");
    ok(strcmp(buffer,"Warning")==0, "incorrect string was returned(%s)\n",buffer); /* string not touched */
    ok(len == 6, "Invalid length (exp. 6, got %d)\n", len); /* unlike success, the length includes the NULL-terminator */

    /* a call with NULL will fail but will return the length */
    index = 0;
    len = sizeof(buffer);
    SetLastError(0xdeadbeef);
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_RAW_HEADERS_CRLF|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                NULL,&len,&index) == FALSE,"Query worked\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Unexpected last error: %d\n", GetLastError());
    ok(len > 40, "Invalid length (exp. more than 40, got %d)\n", len);
    ok(index == 0, "Index was incremented\n");

    /* even for a len that is too small */
    index = 0;
    len = 15;
    SetLastError(0xdeadbeef);
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_RAW_HEADERS_CRLF|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                NULL,&len,&index) == FALSE,"Query worked\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Unexpected last error: %d\n", GetLastError());
    ok(len > 40, "Invalid length (exp. more than 40, got %d)\n", len);
    ok(index == 0, "Index was incremented\n");

    index = 0;
    len = 0;
    SetLastError(0xdeadbeef);
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_RAW_HEADERS_CRLF|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                NULL,&len,&index) == FALSE,"Query worked\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Unexpected last error: %d\n", GetLastError());
    ok(len > 40, "Invalid length (exp. more than 40, got %d)\n", len);
    ok(index == 0, "Index was incremented\n");
    oldlen = len;   /* bytes; at least long enough to hold buffer & nul */


    /* a working query */
    index = 0;
    len = sizeof(buffer);
    memset(buffer, 'x', sizeof(buffer));
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_RAW_HEADERS_CRLF|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index),"Unable to query header\n");
    ok(len + sizeof(CHAR) <= oldlen, "Result longer than advertised\n");
    ok((len < sizeof(buffer)-sizeof(CHAR)) && (buffer[len/sizeof(CHAR)] == 0),"No NUL at end\n");
    ok(len == strlen(buffer) * sizeof(CHAR), "Length wrong\n");
    /* what's in the middle differs between Wine and Windows so currently we check only the beginning and the end */
    ok(strncmp(buffer, "POST /tests/post.php HTTP/1", 25)==0, "Invalid beginning of headers string\n");
    ok(strcmp(buffer + strlen(buffer) - 4, "\r\n\r\n")==0, "Invalid end of headers string\n");
    ok(index == 0, "Index was incremented\n");

    /* Like above two tests, but for W version */

    index = 0;
    len = 0;
    SetLastError(0xdeadbeef);
    ok(HttpQueryInfoW(hRequest,HTTP_QUERY_RAW_HEADERS_CRLF|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                NULL,&len,&index) == FALSE,"Query worked\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Unexpected last error: %d\n", GetLastError());
    ok(len > 80, "Invalid length (exp. more than 80, got %d)\n", len);
    ok(index == 0, "Index was incremented\n");
    oldlen = len;   /* bytes; at least long enough to hold buffer & nul */

    /* a working query */
    index = 0;
    len = sizeof(wbuffer);
    memset(wbuffer, 'x', sizeof(wbuffer));
    ok(HttpQueryInfoW(hRequest,HTTP_QUERY_RAW_HEADERS_CRLF|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                wbuffer,&len,&index),"Unable to query header\n");
    ok(len + sizeof(WCHAR) <= oldlen, "Result longer than advertised\n");
    ok(len == lstrlenW(wbuffer) * sizeof(WCHAR), "Length wrong\n");
    ok((len < sizeof(wbuffer)-sizeof(WCHAR)) && (wbuffer[len/sizeof(WCHAR)] == 0),"No NUL at end\n");
    ok(index == 0, "Index was incremented\n");

    /* end of W version tests */

    /* Without HTTP_QUERY_FLAG_REQUEST_HEADERS */
    index = 0;
    len = sizeof(buffer);
    memset(buffer, 'x', sizeof(buffer));
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_RAW_HEADERS_CRLF,
                buffer,&len,&index) == TRUE,"Query failed\n");
    ok(len == 2 || len == 4 /* win10 */, "Expected 2 or 4, got %d\n", len);
    ok(memcmp(buffer, "\r\n\r\n", len) == 0, "Expected CRLF, got '%s'\n", buffer);
    ok(index == 0, "Index was incremented\n");

    ok(HttpAddRequestHeadersA(hRequest,"Warning:test2",-1,HTTP_ADDREQ_FLAG_ADD),
            "Failed to add duplicate header using HTTP_ADDREQ_FLAG_ADD\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"test1")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index),"Failed to get second header\n");
    ok(index == 2, "Index was not incremented\n");
    ok(strcmp(buffer,"test2")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index)==0,"Third Header Should Not Exist\n");

    ok(HttpAddRequestHeadersA(hRequest,"Warning:test3",-1,HTTP_ADDREQ_FLAG_REPLACE), "Failed to replace header using HTTP_ADDREQ_FLAG_REPLACE\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"test2")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index),"Failed to get second header\n");
    ok(index == 2, "Index was not incremented\n");
    ok(strcmp(buffer,"test3")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index)==0,"Third Header Should Not Exist\n");

    ok(HttpAddRequestHeadersA(hRequest,"Warning:test4",-1,HTTP_ADDREQ_FLAG_ADD_IF_NEW)==0, "HTTP_ADDREQ_FLAG_ADD_IF_NEW replaced existing header\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"test2")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index),"Failed to get second header\n");
    ok(index == 2, "Index was not incremented\n");
    ok(strcmp(buffer,"test3")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index)==0,"Third Header Should Not Exist\n");

    ok(HttpAddRequestHeadersA(hRequest,"Warning:test4",-1, HTTP_ADDREQ_FLAG_COALESCE), "HTTP_ADDREQ_FLAG_COALESCE Did not work\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS,
                buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"test2, test4")==0, "incorrect string was returned(%s)\n", buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Failed to get second header\n");
    ok(index == 2, "Index was not incremented\n");
    ok(strcmp(buffer,"test3")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index)==0,"Third Header Should Not Exist\n");

    ok(HttpAddRequestHeadersA(hRequest,"Warning:test5",-1, HTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA), "HTTP_ADDREQ_FLAG_COALESCE Did not work\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"test2, test4, test5")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Failed to get second header\n");
    ok(index == 2, "Index was not incremented\n");
    ok(strcmp(buffer,"test3")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index)==0,"Third Header Should Not Exist\n");

    ok(HttpAddRequestHeadersA(hRequest,"Warning:test6",-1, HTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON), "HTTP_ADDREQ_FLAG_COALESCE Did not work\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"test2, test4, test5; test6")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Failed to get second header\n");
    ok(index == 2, "Index was not incremented\n");
    ok(strcmp(buffer,"test3")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index)==0,"Third Header Should Not Exist\n");

    ok(HttpAddRequestHeadersA(hRequest,"Warning:test7",-1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE), "HTTP_ADDREQ_FLAG_ADD with HTTP_ADDREQ_FLAG_REPALCE Did not work\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"test3")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Failed to get second header\n");
    ok(index == 2, "Index was not incremented\n");
    ok(strcmp(buffer,"test7")==0, "incorrect string was returned(%s)\n",buffer);
    len = sizeof(buffer);
    strcpy(buffer,"Warning");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index)==0,"Third Header Should Not Exist\n");

    /* Ensure that blank headers are ignored and don't cause a failure */
    ok(HttpAddRequestHeadersA(hRequest,"\r\nBlankTest:value\r\n\r\n",-1, HTTP_ADDREQ_FLAG_ADD_IF_NEW), "Failed to add header with blank entries in list\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"BlankTest");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"value")==0, "incorrect string was returned(%s)\n",buffer);

    /* Ensure that malformed header separators are ignored and don't cause a failure */
    ok(HttpAddRequestHeadersA(hRequest,"\r\rMalformedTest:value\n\nMalformedTestTwo: value2\rMalformedTestThree: value3\n\n\r\r\n",-1, HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE),
        "Failed to add header with malformed entries in list\n");

    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"MalformedTest");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"value")==0, "incorrect string was returned(%s)\n",buffer);
    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"MalformedTestTwo");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"value2")==0, "incorrect string was returned(%s)\n",buffer);
    index = 0;
    len = sizeof(buffer);
    strcpy(buffer,"MalformedTestThree");
    ok(HttpQueryInfoA(hRequest,HTTP_QUERY_CUSTOM|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer,&len,&index),"Unable to query header\n");
    ok(index == 1, "Index was not incremented\n");
    ok(strcmp(buffer,"value3")==0, "incorrect string was returned(%s)\n",buffer);

    ret = HttpAddRequestHeadersA(hRequest, "Authorization: Basic\r\n", -1, HTTP_ADDREQ_FLAG_ADD);
    ok(ret, "unable to add header %u\n", GetLastError());

    index = 0;
    buffer[0] = 0;
    len = sizeof(buffer);
    ret = HttpQueryInfoA(hRequest, HTTP_QUERY_AUTHORIZATION|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer, &len, &index);
    ok(ret, "unable to query header %u\n", GetLastError());
    ok(index == 1, "index was not incremented\n");
    ok(!strcmp(buffer, "Basic"), "incorrect string was returned (%s)\n", buffer);

    ret = HttpAddRequestHeadersA(hRequest, "Authorization:\r\n", -1, HTTP_ADDREQ_FLAG_REPLACE);
    ok(ret, "unable to remove header %u\n", GetLastError());

    index = 0;
    len = sizeof(buffer);
    SetLastError(0xdeadbeef);
    ok(!HttpQueryInfoA(hRequest, HTTP_QUERY_AUTHORIZATION|HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer, &len, &index),
       "header still present\n");
    ok(GetLastError() == ERROR_HTTP_HEADER_NOT_FOUND, "got %u\n", GetLastError());

    ok(InternetCloseHandle(hRequest), "Close request handle failed\n");
done:
    ok(InternetCloseHandle(hConnect), "Close connect handle failed\n");
    ok(InternetCloseHandle(hSession), "Close session handle failed\n");
}