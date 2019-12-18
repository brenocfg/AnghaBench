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
typedef  int /*<<< orphan*/  filler ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_INSUFFICIENT_BUFFER ; 
 int FALSE ; 
 int GetLastError () ; 
 int GetUserNameA (char*,int*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TRUE ; 
 int UNLEN ; 
 scalar_t__ broken (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GetUserNameA(void)
{
    char buffer[UNLEN + 1], filler[UNLEN + 1];
    DWORD required_len, buffer_len;
    BOOL ret;

    /* Test crashes on Windows. */
    if (0)
    {
        SetLastError(0xdeadbeef);
        GetUserNameA(NULL, NULL);
    }

    SetLastError(0xdeadbeef);
    required_len = 0;
    ret = GetUserNameA(NULL, &required_len);
    ok(ret == FALSE, "GetUserNameA returned %d\n", ret);
    ok(required_len != 0, "Outputted buffer length was %u\n", required_len);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Last error was %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    required_len = 1;
    ret = GetUserNameA(NULL, &required_len);
    ok(ret == FALSE, "GetUserNameA returned %d\n", ret);
    ok(required_len != 0 && required_len != 1, "Outputted buffer length was %u\n", required_len);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Last error was %u\n", GetLastError());

    /* Tests crashes on Windows. */
    if (0)
    {
        SetLastError(0xdeadbeef);
        required_len = UNLEN + 1;
        GetUserNameA(NULL, &required_len);

        SetLastError(0xdeadbeef);
        GetUserNameA(buffer, NULL);
    }

    memset(filler, 'x', sizeof(filler));

    /* Note that GetUserNameA on XP and newer outputs the number of bytes
     * required for a Unicode string, which affects a test in the next block. */
    SetLastError(0xdeadbeef);
    memcpy(buffer, filler, sizeof(filler));
    required_len = 0;
    ret = GetUserNameA(buffer, &required_len);
    ok(ret == FALSE, "GetUserNameA returned %d\n", ret);
    ok(!memcmp(buffer, filler, sizeof(filler)), "Output buffer was altered\n");
    ok(required_len != 0, "Outputted buffer length was %u\n", required_len);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Last error was %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    memcpy(buffer, filler, sizeof(filler));
    buffer_len = required_len;
    ret = GetUserNameA(buffer, &buffer_len);
    ok(ret == TRUE, "GetUserNameA returned %d, last error %u\n", ret, GetLastError());
    ok(memcmp(buffer, filler, sizeof(filler)) != 0, "Output buffer was untouched\n");
    ok(buffer_len == required_len ||
       broken(buffer_len == required_len / sizeof(WCHAR)), /* XP+ */
       "Outputted buffer length was %u\n", buffer_len);

    /* Use the reported buffer size from the last GetUserNameA call and pass
     * a length that is one less than the required value. */
    SetLastError(0xdeadbeef);
    memcpy(buffer, filler, sizeof(filler));
    buffer_len--;
    ret = GetUserNameA(buffer, &buffer_len);
    ok(ret == FALSE, "GetUserNameA returned %d\n", ret);
    ok(!memcmp(buffer, filler, sizeof(filler)), "Output buffer was untouched\n");
    ok(buffer_len == required_len, "Outputted buffer length was %u\n", buffer_len);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Last error was %u\n", GetLastError());
}