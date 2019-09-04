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
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * emptyW ; 
 int /*<<< orphan*/  ok (int,char*,int,int,scalar_t__,int,int) ; 
 int pEnumPorts (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*,int*) ; 
 int /*<<< orphan*/ * server_does_not_existW ; 

__attribute__((used)) static void test_EnumPorts(void)
{
    DWORD   res;
    DWORD   level;
    LPBYTE  buffer;
    DWORD   cbBuf;
    DWORD   pcbNeeded;
    DWORD   pcReturned;

    if (!pEnumPorts) return;

    /* valid levels are 1 and 2 */
    for(level = 0; level < 4; level++) {

        cbBuf = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = pEnumPorts(NULL, level, NULL, 0, &cbBuf, &pcReturned);

        /* use only a short test, when we test with an invalid level */
        if(!level || (level > 2)) {
            /* NT4 fails with ERROR_INVALID_LEVEL (as expected)
               XP succeeds with ERROR_SUCCESS () */
            ok( (cbBuf == 0) && (pcReturned == 0),
                "(%d) returned %d with %u and %d, %d (expected 0, 0)\n",
                level, res, GetLastError(), cbBuf, pcReturned);
            continue;
        }        

        ok( !res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER),
            "(%d) returned %d with %u and %d, %d (expected '0' with "
            "ERROR_INSUFFICIENT_BUFFER)\n",
            level, res, GetLastError(), cbBuf, pcReturned);

        buffer = HeapAlloc(GetProcessHeap(), 0, cbBuf * 2);
        if (buffer == NULL) continue;

        pcbNeeded = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = pEnumPorts(NULL, level, buffer, cbBuf, &pcbNeeded, &pcReturned);
        ok( res, "(%d) returned %d with %u and %d, %d (expected '!= 0')\n",
            level, res, GetLastError(), pcbNeeded, pcReturned);
        /* We can compare the returned Data with the Registry / "win.ini",[Ports] here */

        pcbNeeded = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = pEnumPorts(NULL, level, buffer, cbBuf+1, &pcbNeeded, &pcReturned);
        ok( res, "(%d) returned %d with %u and %d, %d (expected '!= 0')\n",
            level, res, GetLastError(), pcbNeeded, pcReturned);

        pcbNeeded = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = pEnumPorts(NULL, level, buffer, cbBuf-1, &pcbNeeded, &pcReturned);
        ok( !res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER),
            "(%d) returned %d with %u and %d, %d (expected '0' with "
            "ERROR_INSUFFICIENT_BUFFER)\n",
            level, res, GetLastError(), pcbNeeded, pcReturned);

        if (0)
        {
            /* The following tests crash this app with native localmon/localspl */
            pEnumPorts(NULL, level, NULL, cbBuf, &pcbNeeded, &pcReturned);
            pEnumPorts(NULL, level, buffer, cbBuf, NULL, &pcReturned);
            pEnumPorts(NULL, level, buffer, cbBuf, &pcbNeeded, NULL);
        }

        /* The Servername is ignored */
        pcbNeeded = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = pEnumPorts(emptyW, level, buffer, cbBuf+1, &pcbNeeded, &pcReturned);
        ok( res, "(%d) returned %d with %u and %d, %d (expected '!= 0')\n",
            level, res, GetLastError(), pcbNeeded, pcReturned);

        pcbNeeded = 0xdeadbeef;
        pcReturned = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        res = pEnumPorts(server_does_not_existW, level, buffer, cbBuf+1, &pcbNeeded, &pcReturned);
        ok( res, "(%d) returned %d with %u and %d, %d (expected '!= 0')\n",
            level, res, GetLastError(), pcbNeeded, pcReturned);

        HeapFree(GetProcessHeap(), 0, buffer);
    }
}