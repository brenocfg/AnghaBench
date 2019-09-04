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
typedef  char* LPSTR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  foobarW ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__,...) ; 

__attribute__((used)) static void test_destination_buffer(void)
{
    LPSTR   buffer;
    INT     maxsize;
    INT     needed;
    INT     len;

    SetLastError(0xdeadbeef);
    needed = WideCharToMultiByte(CP_ACP, 0, foobarW, -1, NULL, 0, NULL, NULL);
    ok( (needed > 0), "returned %d with %u (expected '> 0')\n",
        needed, GetLastError());

    maxsize = needed*2;
    buffer = HeapAlloc(GetProcessHeap(), 0, maxsize);
    if (buffer == NULL) return;

    maxsize--;
    memset(buffer, 'x', maxsize);
    buffer[maxsize] = '\0';
    SetLastError(0xdeadbeef);
    len = WideCharToMultiByte(CP_ACP, 0, foobarW, -1, buffer, needed+1, NULL, NULL);
    ok( (len > 0), "returned %d with %u and '%s' (expected '> 0')\n",
        len, GetLastError(), buffer);

    memset(buffer, 'x', maxsize);
    buffer[maxsize] = '\0';
    SetLastError(0xdeadbeef);
    len = WideCharToMultiByte(CP_ACP, 0, foobarW, -1, buffer, needed, NULL, NULL);
    ok( (len > 0), "returned %d with %u and '%s' (expected '> 0')\n",
        len, GetLastError(), buffer);

    memset(buffer, 'x', maxsize);
    buffer[maxsize] = '\0';
    SetLastError(0xdeadbeef);
    len = WideCharToMultiByte(CP_ACP, 0, foobarW, -1, buffer, needed-1, NULL, NULL);
    ok( !len && (GetLastError() == ERROR_INSUFFICIENT_BUFFER),
        "returned %d with %u and '%s' (expected '0' with "
        "ERROR_INSUFFICIENT_BUFFER)\n", len, GetLastError(), buffer);

    memset(buffer, 'x', maxsize);
    buffer[maxsize] = '\0';
    SetLastError(0xdeadbeef);
    len = WideCharToMultiByte(CP_ACP, 0, foobarW, -1, buffer, 1, NULL, NULL);
    ok( !len && (GetLastError() == ERROR_INSUFFICIENT_BUFFER),
        "returned %d with %u and '%s' (expected '0' with "
        "ERROR_INSUFFICIENT_BUFFER)\n", len, GetLastError(), buffer);

    SetLastError(0xdeadbeef);
    len = WideCharToMultiByte(CP_ACP, 0, foobarW, -1, buffer, 0, NULL, NULL);
    ok( (len > 0), "returned %d with %u (expected '> 0')\n",
        len, GetLastError());

    SetLastError(0xdeadbeef);
    len = WideCharToMultiByte(CP_ACP, 0, foobarW, -1, NULL, needed, NULL, NULL);
    ok( !len && (GetLastError() == ERROR_INVALID_PARAMETER),
        "returned %d with %u (expected '0' with "
        "ERROR_INVALID_PARAMETER)\n", len, GetLastError());

    HeapFree(GetProcessHeap(), 0, buffer);
}