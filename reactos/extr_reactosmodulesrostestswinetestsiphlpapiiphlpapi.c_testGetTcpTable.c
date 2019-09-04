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
struct TYPE_9__ {int /*<<< orphan*/  dwRemotePort; int /*<<< orphan*/  dwRemoteAddr; int /*<<< orphan*/  dwLocalPort; int /*<<< orphan*/  dwLocalAddr; } ;
struct TYPE_8__ {int /*<<< orphan*/  dwState; } ;
struct TYPE_7__ {scalar_t__ dwNumEntries; TYPE_4__* table; } ;
typedef  TYPE_1__* PMIB_TCPTABLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ ERROR_NO_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ NO_ERROR ; 
 TYPE_3__ U (TYPE_4__) ; 
 scalar_t__ broken (int) ; 
 char* ntoa (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pGetTcpTable (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,...) ; 
 int winetest_debug ; 

__attribute__((used)) static void testGetTcpTable(void)
{
  if (pGetTcpTable) {
    DWORD apiReturn;
    ULONG dwSize = 0;

    apiReturn = pGetTcpTable(NULL, &dwSize, FALSE);
    if (apiReturn == ERROR_NOT_SUPPORTED) {
      skip("GetTcpTable is not supported\n");
      return;
    }
    ok(apiReturn == ERROR_INSUFFICIENT_BUFFER ||
       broken(apiReturn == ERROR_NO_DATA), /* win95 */
     "GetTcpTable(NULL, &dwSize, FALSE) returned %d, expected ERROR_INSUFFICIENT_BUFFER\n",
     apiReturn);
    if (apiReturn == ERROR_INSUFFICIENT_BUFFER) {
      PMIB_TCPTABLE buf = HeapAlloc(GetProcessHeap(), 0, dwSize);

      apiReturn = pGetTcpTable(buf, &dwSize, FALSE);
      ok(apiReturn == NO_ERROR,
       "GetTcpTable(buf, &dwSize, FALSE) returned %d, expected NO_ERROR\n",
       apiReturn);

      if (apiReturn == NO_ERROR && winetest_debug > 1)
      {
          DWORD i;
          trace( "TCP table: %u entries\n", buf->dwNumEntries );
          for (i = 0; i < buf->dwNumEntries; i++)
          {
              char buffer[40];
              sprintf( buffer, "local %s:%u",
                       ntoa(buf->table[i].dwLocalAddr), ntohs(buf->table[i].dwLocalPort) );
              trace( "%u: %s remote %s:%u state %u\n",
                     i, buffer, ntoa( buf->table[i].dwRemoteAddr ),
                     ntohs(buf->table[i].dwRemotePort), U(buf->table[i]).dwState );
          }
      }
      HeapFree(GetProcessHeap(), 0, buf);
    }
  }
}