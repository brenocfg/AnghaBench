#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_9__ {int /*<<< orphan*/  dwForwardIfIndex; int /*<<< orphan*/  dwForwardNextHop; int /*<<< orphan*/  dwForwardMask; int /*<<< orphan*/  dwForwardDest; } ;
struct TYPE_8__ {int /*<<< orphan*/  dwForwardType; } ;
struct TYPE_7__ {scalar_t__ dwNumEntries; TYPE_4__* table; } ;
typedef  TYPE_1__* PMIB_IPFORWARDTABLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ NO_ERROR ; 
 TYPE_3__ U1 (TYPE_4__) ; 
 char* ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pGetIpForwardTable (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,...) ; 
 int winetest_debug ; 

__attribute__((used)) static void testGetIpForwardTable(void)
{
  if (pGetIpForwardTable) {
    DWORD apiReturn;
    ULONG dwSize = 0;

    apiReturn = pGetIpForwardTable(NULL, NULL, FALSE);
    if (apiReturn == ERROR_NOT_SUPPORTED) {
      skip("GetIpForwardTable is not supported\n");
      return;
    }
    ok(apiReturn == ERROR_INVALID_PARAMETER,
     "GetIpForwardTable(NULL, NULL, FALSE) returned %d, expected ERROR_INVALID_PARAMETER\n",
     apiReturn);
    apiReturn = pGetIpForwardTable(NULL, &dwSize, FALSE);
    ok(apiReturn == ERROR_INSUFFICIENT_BUFFER,
     "GetIpForwardTable(NULL, &dwSize, FALSE) returned %d, expected ERROR_INSUFFICIENT_BUFFER\n",
     apiReturn);
    if (apiReturn == ERROR_INSUFFICIENT_BUFFER) {
      PMIB_IPFORWARDTABLE buf = HeapAlloc(GetProcessHeap(), 0, dwSize);

      apiReturn = pGetIpForwardTable(buf, &dwSize, FALSE);
      ok(apiReturn == NO_ERROR,
       "GetIpForwardTable(buf, &dwSize, FALSE) returned %d, expected NO_ERROR\n",
       apiReturn);

      if (apiReturn == NO_ERROR && winetest_debug > 1)
      {
          DWORD i;

          trace( "IP forward table: %u entries\n", buf->dwNumEntries );
          for (i = 0; i < buf->dwNumEntries; i++)
          {
              char buffer[100];
              sprintf( buffer, "dest %s", ntoa( buf->table[i].dwForwardDest ));
              sprintf( buffer + strlen(buffer), " mask %s", ntoa( buf->table[i].dwForwardMask ));
              trace( "%u: %s gw %s if %u type %u\n", i, buffer,
                     ntoa( buf->table[i].dwForwardNextHop ),
                     buf->table[i].dwForwardIfIndex, U1(buf->table[i]).dwForwardType );
          }
      }
      HeapFree(GetProcessHeap(), 0, buf);
    }
  }
}