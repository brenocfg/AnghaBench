#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {int dwNumEntries; TYPE_1__* table; } ;
struct TYPE_6__ {scalar_t__ wType; int /*<<< orphan*/  dwIndex; int /*<<< orphan*/  dwAddr; } ;
typedef  TYPE_2__* PMIB_IPADDRTABLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 scalar_t__ pGetIpAddrTable (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  testGetIfEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void testGetIpAddrTable(void)
{
  if (pGetIpAddrTable) {
    DWORD apiReturn;
    ULONG dwSize = 0;

    apiReturn = pGetIpAddrTable(NULL, NULL, FALSE);
    if (apiReturn == ERROR_NOT_SUPPORTED) {
      skip("GetIpAddrTable is not supported\n");
      return;
    }
    ok(apiReturn == ERROR_INVALID_PARAMETER,
     "GetIpAddrTable(NULL, NULL, FALSE) returned %d, expected ERROR_INVALID_PARAMETER\n",
     apiReturn);
    apiReturn = pGetIpAddrTable(NULL, &dwSize, FALSE);
    ok(apiReturn == ERROR_INSUFFICIENT_BUFFER,
     "GetIpAddrTable(NULL, &dwSize, FALSE) returned %d, expected ERROR_INSUFFICIENT_BUFFER\n",
     apiReturn);
    if (apiReturn == ERROR_INSUFFICIENT_BUFFER) {
      PMIB_IPADDRTABLE buf = HeapAlloc(GetProcessHeap(), 0, dwSize);

      apiReturn = pGetIpAddrTable(buf, &dwSize, FALSE);
      ok(apiReturn == NO_ERROR,
       "GetIpAddrTable(buf, &dwSize, FALSE) returned %d, expected NO_ERROR\n",
       apiReturn);
      if (apiReturn == NO_ERROR && buf->dwNumEntries)
      {
        int i;
        testGetIfEntry(buf->table[0].dwIndex);
        for (i = 0; i < buf->dwNumEntries; i++)
        {
          ok (buf->table[i].wType != 0, "Test[%d]: expected wType > 0\n", i);
          trace("Entry[%d]: addr %s, dwIndex %u, wType 0x%x\n", i,
                ntoa(buf->table[i].dwAddr), buf->table[i].dwIndex, buf->table[i].wType);
        }
      }
      HeapFree(GetProcessHeap(), 0, buf);
    }
  }
}