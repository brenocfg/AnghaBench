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
typedef  char CHAR ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int GetSystemDirectoryA (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__,...) ; 

__attribute__((used)) static void test_GetSystemDirectory(void)
{
    CHAR    buffer[MAX_PATH + 4];
    DWORD   res;
    DWORD   total;

    SetLastError(0xdeadbeef);
    res = GetSystemDirectoryA(NULL, 0);
    /* res includes the terminating Zero */
    ok(res > 0, "returned %d with %d (expected '>0')\n", res, GetLastError());

    total = res;

    /* this crashes on XP */
    if (0)
        GetSystemDirectoryA(NULL, total);

    SetLastError(0xdeadbeef);
    res = GetSystemDirectoryA(NULL, total-1);
    /* 95+NT: total (includes the terminating Zero)
       98+ME: 0 with ERROR_INVALID_PARAMETER */
    ok( (res == total) || (!res && (GetLastError() == ERROR_INVALID_PARAMETER)),
        "returned %d with %d (expected '%d' or: '0' with "
        "ERROR_INVALID_PARAMETER)\n", res, GetLastError(), total);

    if (total > MAX_PATH) return;

    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetSystemDirectoryA(buffer, total);
    /* res does not include the terminating Zero */
    ok( (res == (total-1)) && (buffer[0]),
        "returned %d with %d and '%s' (expected '%d' and a string)\n",
        res, GetLastError(), buffer, total-1);

    buffer[0] = '\0';
    SetLastError(0xdeadbeef);
    res = GetSystemDirectoryA(buffer, total + 1);
    /* res does not include the terminating Zero */
    ok( (res == (total-1)) && (buffer[0]),
        "returned %d with %d and '%s' (expected '%d' and a string)\n",
        res, GetLastError(), buffer, total-1);

    memset(buffer, '#', total + 1);
    buffer[total + 2] = '\0';
    SetLastError(0xdeadbeef);
    res = GetSystemDirectoryA(buffer, total-1);
    /* res includes the terminating Zero) */
    ok( res == total, "returned %d with %d and '%s' (expected '%d')\n",
        res, GetLastError(), buffer, total);

    memset(buffer, '#', total + 1);
    buffer[total + 2] = '\0';
    SetLastError(0xdeadbeef);
    res = GetSystemDirectoryA(buffer, total-2);
    /* res includes the terminating Zero) */
    ok( res == total, "returned %d with %d and '%s' (expected '%d')\n",
        res, GetLastError(), buffer, total);
}