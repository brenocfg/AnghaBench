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
typedef  int /*<<< orphan*/  value_nospace ;
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  test_indices ;
typedef  int /*<<< orphan*/  test_header_end ;
typedef  int /*<<< orphan*/  test_header_bytes ;
typedef  int /*<<< orphan*/  test_header_begin ;
typedef  int /*<<< orphan*/  test_flag_coalesce_semicolon_reverse ;
typedef  int /*<<< orphan*/  test_flag_coalesce_semicolon ;
typedef  int /*<<< orphan*/  test_flag_coalesce_reverse ;
typedef  int /*<<< orphan*/  test_flag_coalesce_comma_reverse ;
typedef  int /*<<< orphan*/  test_flag_coalesce_comma ;
typedef  int /*<<< orphan*/  test_flag_coalesce ;
typedef  int /*<<< orphan*/  full_path_test_header_begin ;
typedef  int /*<<< orphan*/  empty ;
typedef  int /*<<< orphan*/  check_buffer ;
typedef  int /*<<< orphan*/  buffer ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int ERROR_WINHTTP_HEADER_NOT_FOUND ; 
 int ERROR_WINHTTP_NAME_NOT_RESOLVED ; 
 int FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  INTERNET_DEFAULT_HTTP_PORT ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TRUE ; 
 int /*<<< orphan*/  WINHTTP_ACCESS_TYPE_DEFAULT_PROXY ; 
 int WINHTTP_ADDREQ_FLAG_ADD ; 
 int WINHTTP_ADDREQ_FLAG_ADD_IF_NEW ; 
 int WINHTTP_ADDREQ_FLAG_COALESCE ; 
 int WINHTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA ; 
 int WINHTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON ; 
 int WINHTTP_ADDREQ_FLAG_REPLACE ; 
 int /*<<< orphan*/  WINHTTP_DEFAULT_ACCEPT_TYPES ; 
 int /*<<< orphan*/  WINHTTP_NO_PROXY_BYPASS ; 
 int /*<<< orphan*/  WINHTTP_NO_PROXY_NAME ; 
 int /*<<< orphan*/  WINHTTP_NO_REFERER ; 
 int WINHTTP_QUERY_CUSTOM ; 
 int WINHTTP_QUERY_FLAG_REQUEST_HEADERS ; 
 int WINHTTP_QUERY_RAW_HEADERS ; 
 int WINHTTP_QUERY_RAW_HEADERS_CRLF ; 
 int WinHttpAddRequestHeaders (int /*<<< orphan*/ *,char const*,long,int) ; 
 int WinHttpCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WinHttpConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpenRequest (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WinHttpQueryHeaders (int /*<<< orphan*/ *,int,char const*,char*,int*,int*) ; 
 scalar_t__ broken (int) ; 
 int lstrlenW (char const*) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_useragent ; 
 int /*<<< orphan*/  test_winehq ; 

__attribute__((used)) static void test_WinHttpAddHeaders(void)
{
    HINTERNET session, request, connection;
    BOOL ret, reverse;
    WCHAR buffer[MAX_PATH];
    WCHAR check_buffer[MAX_PATH];
    DWORD err, index, len, oldlen;

    static const WCHAR test_file[] = {'/','p','o','s','t','t','e','s','t','.','p','h','p',0};
    static const WCHAR test_verb[] = {'P','O','S','T',0};
    static const WCHAR test_header_begin[] =
        {'P','O','S','T',' ','/','p','o','s','t','t','e','s','t','.','p','h','p',' ','H','T','T','P','/','1'};
    static const WCHAR full_path_test_header_begin[] =
        {'P','O','S','T',' ','h','t','t','p',':','/','/','t','e','s','t','.','w','i','n','e','h','q','.','o','r','g',':','8','0',
         '/','p','o','s','t','t','e','s','t','.','p','h','p',' ','H','T','T','P','/','1'};
    static const WCHAR test_header_end[] = {'\r','\n','\r','\n',0};
    static const WCHAR test_header_name[] = {'W','a','r','n','i','n','g',0};
    static const WCHAR test_header_name2[] = {'n','a','m','e',0};
    static const WCHAR test_header_name3[] = {'a',0};
    static const WCHAR test_header_range[] = {'R','a','n','g','e',0};
    static const WCHAR test_header_range_bytes[] = {'R','a','n','g','e',':',' ','b','y','t','e','s','=','0','-','7','7','3','\r','\n',0};
    static const WCHAR test_header_bytes[] = {'b','y','t','e','s','=','0','-','7','7','3',0};

    static const WCHAR test_flag_coalesce[] = {'t','e','s','t','2',',',' ','t','e','s','t','4',0};
    static const WCHAR test_flag_coalesce_reverse[] = {'t','e','s','t','3',',',' ','t','e','s','t','4',0};
    static const WCHAR test_flag_coalesce_comma[] =
        {'t','e','s','t','2',',',' ','t','e','s','t','4',',',' ','t','e','s','t','5',0};
    static const WCHAR test_flag_coalesce_comma_reverse[] =
        {'t','e','s','t','3',',',' ','t','e','s','t','4',',',' ','t','e','s','t','5',0};
    static const WCHAR test_flag_coalesce_semicolon[] =
        {'t','e','s','t','2',',',' ','t','e','s','t','4',',',' ','t','e','s','t','5',';',' ','t','e','s','t','6',0};
    static const WCHAR test_flag_coalesce_semicolon_reverse[] =
        {'t','e','s','t','3',',',' ','t','e','s','t','4',',',' ','t','e','s','t','5',';',' ','t','e','s','t','6',0};

    static const WCHAR field[] = {'f','i','e','l','d',0};
    static const WCHAR value[] = {'v','a','l','u','e',' ',0};
    static const WCHAR value_nospace[] = {'v','a','l','u','e',0};
    static const WCHAR empty[] = {0};

    static const WCHAR test_headers[][14] =
        {
            {'W','a','r','n','i','n','g',':','t','e','s','t','1',0},
            {'W','a','r','n','i','n','g',':','t','e','s','t','2',0},
            {'W','a','r','n','i','n','g',':','t','e','s','t','3',0},
            {'W','a','r','n','i','n','g',':','t','e','s','t','4',0},
            {'W','a','r','n','i','n','g',':','t','e','s','t','5',0},
            {'W','a','r','n','i','n','g',':','t','e','s','t','6',0},
            {'W','a','r','n','i','n','g',':','t','e','s','t','7',0},
            {0},
            {':',0},
            {'a',':',0},
            {':','b',0},
            {'c','d',0},
            {' ','e',' ',':','f',0},
            {'f','i','e','l','d',':',' ','v','a','l','u','e',' ',0},
            {'n','a','m','e',':',' ','v','a','l','u','e',0},
            {'n','a','m','e',':',0}
        };
    static const WCHAR test_indices[][6] =
        {
            {'t','e','s','t','1',0},
            {'t','e','s','t','2',0},
            {'t','e','s','t','3',0},
            {'t','e','s','t','4',0}
        };

    session = WinHttpOpen(test_useragent, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    ok(session != NULL, "WinHttpOpen failed to open session.\n");

    connection = WinHttpConnect (session, test_winehq, INTERNET_DEFAULT_HTTP_PORT, 0);
    ok(connection != NULL, "WinHttpConnect failed to open a connection, error: %u.\n", GetLastError());

    request = WinHttpOpenRequest(connection, test_verb, test_file, NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
    if (request == NULL && GetLastError() == ERROR_WINHTTP_NAME_NOT_RESOLVED)
    {
        skip("Network unreachable, skipping.\n");
        goto done;
    }
    ok(request != NULL, "WinHttpOpenRequest failed to open a request, error: %u.\n", GetLastError());

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders unexpectedly succeeded, found 'Warning' header.\n");
    SetLastError(0xdeadbeef);
    ret = WinHttpAddRequestHeaders(request, test_headers[0], -1L, WINHTTP_ADDREQ_FLAG_ADD);
    err = GetLastError();
    ok(ret, "WinHttpAddRequestHeaders failed to add new header, got %d with error %u.\n", ret, err);
    ok(err == ERROR_SUCCESS || broken(err == 0xdeadbeef) /* < win7 */, "got %u\n", err);

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 1, "WinHttpQueryHeaders failed: header index not incremented\n");
    ok(memcmp(buffer, test_indices[0], sizeof(test_indices[0])) == 0, "WinHttpQueryHeaders failed: incorrect string returned\n");
    ok(len == 5*sizeof(WCHAR), "WinHttpQueryHeaders failed: invalid length returned, expected 5, got %d\n", len);

    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders unexpectedly succeeded, second index should not exist.\n");

    /* Try to fetch the header info with a buffer that's big enough to fit the
     * string but not the NULL terminator.
     */
    index = 0;
    len = 5*sizeof(WCHAR);
    memset(check_buffer, 0xab, sizeof(check_buffer));
    memcpy(buffer, check_buffer, sizeof(buffer));
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders unexpectedly succeeded with a buffer that's too small.\n");
    ok(memcmp(buffer, check_buffer, sizeof(buffer)) == 0,
            "WinHttpQueryHeaders failed, modified the buffer when it should not have.\n");
    ok(len == 6*sizeof(WCHAR), "WinHttpQueryHeaders returned invalid length, expected 12, got %d\n", len);

    /* Try with a NULL buffer */
    index = 0;
    len = sizeof(buffer);
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_RAW_HEADERS_CRLF | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, NULL, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders unexpectedly succeeded.\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Expected ERROR_INSUFFICIENT_BUFFER, got %u\n", GetLastError());
    ok(len > 40, "WinHttpQueryHeaders returned invalid length: expected greater than 40, got %d\n", len);
    ok(index == 0, "WinHttpQueryHeaders incorrectly incremented header index.\n");

    /* Try with a NULL buffer and a length that's too small */
    index = 0;
    len = 10;
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_RAW_HEADERS_CRLF | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, NULL, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders unexpectedly succeeded.\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
        "WinHttpQueryHeaders set incorrect error: expected ERROR_INSUFFICENT_BUFFER, got %u\n", GetLastError());
    ok(len > 40, "WinHttpQueryHeaders returned invalid length: expected greater than 40, got %d\n", len);
    ok(index == 0, "WinHttpQueryHeaders incorrectly incremented header index.\n");

    index = 0;
    len = 0;
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_RAW_HEADERS_CRLF | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, NULL, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders unexpectedly succeeded.\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
        "WinHttpQueryHeaders set incorrect error: expected ERROR_INSUFFICIENT_BUFFER, got %u\n", GetLastError());
    ok(len > 40, "WinHttpQueryHeaders returned invalid length: expected greater than 40, got %d\n", len);
    ok(index == 0, "WinHttpQueryHeaders failed: index was incremented.\n");

    /* valid query */
    oldlen = len;
    index = 0;
    len = sizeof(buffer);
    memset(buffer, 0xff, sizeof(buffer));
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_RAW_HEADERS_CRLF | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: got %d\n", ret);
    ok(len + sizeof(WCHAR) <= oldlen, "WinHttpQueryHeaders resulting length longer than advertized.\n");
    ok((len < sizeof(buffer) - sizeof(WCHAR)) && buffer[len / sizeof(WCHAR)] == 0, "WinHttpQueryHeaders did not append NULL terminator\n");
    ok(len == lstrlenW(buffer) * sizeof(WCHAR), "WinHttpQueryHeaders returned incorrect length.\n");
    ok(memcmp(buffer, test_header_begin, sizeof(test_header_begin)) == 0 ||
        memcmp(buffer, full_path_test_header_begin, sizeof(full_path_test_header_begin)) == 0,
        "WinHttpQueryHeaders returned invalid beginning of header string.\n");
    ok(memcmp(buffer + lstrlenW(buffer) - 4, test_header_end, sizeof(test_header_end)) == 0,
        "WinHttpQueryHeaders returned invalid end of header string.\n");
    ok(index == 0, "WinHttpQueryHeaders incremented header index.\n");

    index = 0;
    len = 0;
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_RAW_HEADERS | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, NULL, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders unexpectedly succeeded.\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
        "WinHttpQueryHeaders set incorrect error: expected ERROR_INSUFFICIENT_BUFFER, got %u\n", GetLastError());
    ok(len > 40, "WinHttpQueryHeaders returned invalid length: expected greater than 40, got %d\n", len);
    ok(index == 0, "WinHttpQueryHeaders failed: index was incremented.\n");

    oldlen = len;
    index = 0;
    len = sizeof(buffer);
    memset(buffer, 0xff, sizeof(buffer));
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_RAW_HEADERS | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed %u\n", GetLastError());
    ok(len + sizeof(WCHAR) <= oldlen, "resulting length longer than advertized\n");
    ok((len < sizeof(buffer) - sizeof(WCHAR)) && !buffer[len / sizeof(WCHAR)] && !buffer[len / sizeof(WCHAR) - 1],
        "no double NULL terminator\n");
    ok(memcmp(buffer, test_header_begin, sizeof(test_header_begin)) == 0 ||
        memcmp(buffer, full_path_test_header_begin, sizeof(full_path_test_header_begin)) == 0,
        "invalid beginning of header string.\n");
    ok(index == 0, "header index was incremented\n");

    /* tests for more indices */
    ret = WinHttpAddRequestHeaders(request, test_headers[1], -1L, WINHTTP_ADDREQ_FLAG_ADD);
    ok(ret == TRUE, "WinHttpAddRequestHeaders failed to add duplicate header: %d\n", ret);

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 1, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, test_indices[0], sizeof(test_indices[0])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 2, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, test_indices[1], sizeof(test_indices[1])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    ret = WinHttpAddRequestHeaders(request, test_headers[2], -1L, WINHTTP_ADDREQ_FLAG_REPLACE);
    ok(ret == TRUE, "WinHttpAddRequestHeaders failed to add duplicate header.\n");

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 1, "WinHttpQueryHeaders failed to increment index.\n");
    reverse = (memcmp(buffer, test_indices[1], sizeof(test_indices[1])) != 0); /* Win7 returns values in reverse order of adding */
    ok(memcmp(buffer, test_indices[reverse ? 2 : 1], sizeof(test_indices[reverse ? 2 : 1])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 2, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, test_indices[reverse ? 1 : 2], sizeof(test_indices[reverse ? 1 : 2])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    /* add if new flag */
    ret = WinHttpAddRequestHeaders(request, test_headers[3], -1L, WINHTTP_ADDREQ_FLAG_ADD_IF_NEW);
    ok(ret == FALSE, "WinHttpAddRequestHeaders incorrectly replaced existing header.\n");

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 1, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, test_indices[reverse ? 2 : 1], sizeof(test_indices[reverse ? 2 : 1])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 2, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, test_indices[reverse ? 1 : 2], sizeof(test_indices[reverse ? 1 : 2])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders succeeded unexpectedly, found third header.\n");

    /* coalesce flag */
    ret = WinHttpAddRequestHeaders(request, test_headers[3], -1L, WINHTTP_ADDREQ_FLAG_COALESCE);
    ok(ret == TRUE, "WinHttpAddRequestHeaders failed with flag WINHTTP_ADDREQ_FLAG_COALESCE.\n");

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 1, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, reverse ? test_flag_coalesce_reverse : test_flag_coalesce,
                      reverse ? sizeof(test_flag_coalesce_reverse) : sizeof(test_flag_coalesce)) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 2, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, test_indices[reverse ? 1 : 2], sizeof(test_indices[reverse ? 1 : 2])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders succeeded unexpectedly, found third header.\n");

    /* coalesce with comma flag */
    ret = WinHttpAddRequestHeaders(request, test_headers[4], -1L, WINHTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA);
    ok(ret == TRUE, "WinHttpAddRequestHeaders failed with flag WINHTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA.\n");

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 1, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, reverse ? test_flag_coalesce_comma_reverse : test_flag_coalesce_comma,
                      reverse ? sizeof(test_flag_coalesce_comma_reverse) : sizeof(test_flag_coalesce_comma)) == 0,
        "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 2, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, test_indices[reverse ? 1 : 2], sizeof(test_indices[reverse ? 1 : 2])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders succeeded unexpectedly, found third header.\n");


    /* coalesce with semicolon flag */
    ret = WinHttpAddRequestHeaders(request, test_headers[5], -1L, WINHTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON);
    ok(ret == TRUE, "WinHttpAddRequestHeaders failed with flag WINHTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON.\n");

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 1, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, reverse ? test_flag_coalesce_semicolon_reverse : test_flag_coalesce_semicolon,
                      reverse ? sizeof(test_flag_coalesce_semicolon_reverse) : sizeof(test_flag_coalesce_semicolon)) == 0,
            "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 2, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, test_indices[reverse ? 1 : 2], sizeof(test_indices[reverse ? 1 : 2])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders succeeded unexpectedly, found third header.\n");

    /* add and replace flags */
    ret = WinHttpAddRequestHeaders(request, test_headers[3], -1L, WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE);
    ok(ret == TRUE, "WinHttpAddRequestHeaders failed with flag WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE.\n");

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 1, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, test_indices[reverse ? 3 : 2], sizeof(test_indices[reverse ? 3 : 2])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == TRUE, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(index == 2, "WinHttpQueryHeaders failed to increment index.\n");
    ok(memcmp(buffer, test_indices[reverse ? 1 : 3], sizeof(test_indices[reverse ? 1 : 3])) == 0, "WinHttpQueryHeaders returned incorrect string.\n");

    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        test_header_name, buffer, &len, &index);
    ok(ret == FALSE, "WinHttpQueryHeaders succeeded unexpectedly, found third header.\n");

    ret = WinHttpAddRequestHeaders(request, test_headers[8], ~0u, WINHTTP_ADDREQ_FLAG_ADD);
    ok(!ret, "WinHttpAddRequestHeaders failed\n");

    ret = WinHttpAddRequestHeaders(request, test_headers[9], ~0u, WINHTTP_ADDREQ_FLAG_ADD);
    ok(ret, "WinHttpAddRequestHeaders failed\n");

    index = 0;
    memset(buffer, 0xff, sizeof(buffer));
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
                              test_header_name3, buffer, &len, &index);
    ok(ret, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(!memcmp(buffer, empty, sizeof(empty)), "unexpected result\n");

    ret = WinHttpAddRequestHeaders(request, test_headers[10], ~0u, WINHTTP_ADDREQ_FLAG_ADD);
    ok(!ret, "WinHttpAddRequestHeaders failed\n");

    ret = WinHttpAddRequestHeaders(request, test_headers[11], ~0u, WINHTTP_ADDREQ_FLAG_ADD);
    ok(!ret, "WinHttpAddRequestHeaders failed\n");

    ret = WinHttpAddRequestHeaders(request, test_headers[12], ~0u, WINHTTP_ADDREQ_FLAG_ADD);
    ok(!ret, "WinHttpAddRequestHeaders failed\n");

    ret = WinHttpAddRequestHeaders(request, test_headers[13], ~0u, WINHTTP_ADDREQ_FLAG_ADD);
    ok(ret, "WinHttpAddRequestHeaders failed\n");

    index = 0;
    buffer[0] = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
        field, buffer, &len, &index);
    ok(ret, "WinHttpQueryHeaders failed: %u\n", GetLastError());
    ok(!memcmp(buffer, value, sizeof(value)) || ! memcmp(buffer, value_nospace, sizeof(value_nospace)), "unexpected result\n");

    SetLastError(0xdeadbeef);
    ret = WinHttpAddRequestHeaders(request, test_header_range_bytes, 0,
                                   WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE);
    err = GetLastError();
    ok(!ret, "unexpected success\n");
    ok(err == ERROR_INVALID_PARAMETER, "got %u\n", err);

    ret = WinHttpAddRequestHeaders(request, test_header_range_bytes, ~0u,
                                   WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE);
    ok(ret, "failed to add header: %u\n", GetLastError());

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
                              test_header_range, buffer, &len, &index);
    ok(ret, "failed to get range header %u\n", GetLastError());
    ok(!memcmp(buffer, test_header_bytes, sizeof(test_header_bytes)), "incorrect string returned\n");
    ok(len == lstrlenW(test_header_bytes) * sizeof(WCHAR), "wrong length %u\n", len);
    ok(index == 1, "wrong index %u\n", index);

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
                              test_header_name2, buffer, &len, &index);
    ok(!ret, "unexpected success\n");

    SetLastError(0xdeadbeef);
    ret = WinHttpAddRequestHeaders(request, test_headers[14], ~0u, WINHTTP_ADDREQ_FLAG_REPLACE);
    err = GetLastError();
    ok(!ret, "unexpected success\n");
    ok(err == ERROR_WINHTTP_HEADER_NOT_FOUND, "got %u\n", err);

    ret = WinHttpAddRequestHeaders(request, test_headers[14], ~0u, WINHTTP_ADDREQ_FLAG_ADD);
    ok(ret, "got %u\n", GetLastError());

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
                              test_header_name2, buffer, &len, &index);
    ok(ret, "got %u\n", GetLastError());
    ok(index == 1, "wrong index %u\n", index);
    ok(!memcmp(buffer, value_nospace, sizeof(value_nospace)), "incorrect string\n");

    ret = WinHttpAddRequestHeaders(request, test_headers[15], ~0u, WINHTTP_ADDREQ_FLAG_REPLACE);
    ok(ret, "got %u\n", GetLastError());

    index = 0;
    len = sizeof(buffer);
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
                              test_header_name2, buffer, &len, &index);
    err = GetLastError();
    ok(!ret, "unexpected success\n");
    ok(err == ERROR_WINHTTP_HEADER_NOT_FOUND, "got %u\n", err);

    ret = WinHttpAddRequestHeaders(request, test_headers[14], -1L, 0);
    ok(ret, "got %u\n", GetLastError());

    index = 0;
    len = sizeof(buffer);
    ret = WinHttpQueryHeaders(request, WINHTTP_QUERY_CUSTOM | WINHTTP_QUERY_FLAG_REQUEST_HEADERS,
                              test_header_name2, buffer, &len, &index);
    ok(ret, "got %u\n", GetLastError());
    ok(index == 1, "wrong index %u\n", index);
    ok(!memcmp(buffer, value_nospace, sizeof(value_nospace)), "incorrect string\n");

    ret = WinHttpCloseHandle(request);
    ok(ret == TRUE, "WinHttpCloseHandle failed on closing request, got %d.\n", ret);
 done:
    ret = WinHttpCloseHandle(connection);
    ok(ret == TRUE, "WinHttpCloseHandle failed on closing connection, got %d.\n", ret);
    ret = WinHttpCloseHandle(session);
    ok(ret == TRUE, "WinHttpCloseHandle failed on closing session, got %d.\n", ret);

}