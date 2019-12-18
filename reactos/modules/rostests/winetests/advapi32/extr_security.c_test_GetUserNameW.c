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
 int GetUserNameW (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TRUE ; 
 int UNLEN ; 
 scalar_t__ broken (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GetUserNameW(void)
{
    WCHAR buffer[UNLEN + 1], filler[UNLEN + 1];
    DWORD required_len, buffer_len;
    BOOL ret;

    /* Test crashes on Windows. */
    if (0)
    {
        SetLastError(0xdeadbeef);
        GetUserNameW(NULL, NULL);
    }

    SetLastError(0xdeadbeef);
    required_len = 0;
    ret = GetUserNameW(NULL, &required_len);
    ok(ret == FALSE, "GetUserNameW returned %d\n", ret);
    ok(required_len != 0, "Outputted buffer length was %u\n", required_len);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Last error was %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    required_len = 1;
    ret = GetUserNameW(NULL, &required_len);
    ok(ret == FALSE, "GetUserNameW returned %d\n", ret);
    ok(required_len != 0 && required_len != 1, "Outputted buffer length was %u\n", required_len);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Last error was %u\n", GetLastError());

    /* Tests crash on Windows. */
    if (0)
    {
        SetLastError(0xdeadbeef);
        required_len = UNLEN + 1;
        GetUserNameW(NULL, &required_len);

        SetLastError(0xdeadbeef);
        GetUserNameW(buffer, NULL);
    }

    memset(filler, 'x', sizeof(filler));

    SetLastError(0xdeadbeef);
    memcpy(buffer, filler, sizeof(filler));
    required_len = 0;
    ret = GetUserNameW(buffer, &required_len);
    ok(ret == FALSE, "GetUserNameW returned %d\n", ret);
    ok(!memcmp(buffer, filler, sizeof(filler)), "Output buffer was altered\n");
    ok(required_len != 0, "Outputted buffer length was %u\n", required_len);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Last error was %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    memcpy(buffer, filler, sizeof(filler));
    buffer_len = required_len;
    ret = GetUserNameW(buffer, &buffer_len);
    ok(ret == TRUE, "GetUserNameW returned %d, last error %u\n", ret, GetLastError());
    ok(memcmp(buffer, filler, sizeof(filler)) != 0, "Output buffer was untouched\n");
    ok(buffer_len == required_len, "Outputted buffer length was %u\n", buffer_len);

    /* GetUserNameW on XP and newer writes a truncated portion of the username string to the buffer. */
    SetLastError(0xdeadbeef);
    memcpy(buffer, filler, sizeof(filler));
    buffer_len--;
    ret = GetUserNameW(buffer, &buffer_len);
    ok(ret == FALSE, "GetUserNameW returned %d\n", ret);
    ok(!memcmp(buffer, filler, sizeof(filler)) ||
       broken(memcmp(buffer, filler, sizeof(filler)) != 0), /* XP+ */
       "Output buffer was altered\n");
    ok(buffer_len == required_len, "Outputted buffer length was %u\n", buffer_len);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Last error was %u\n", GetLastError());
}