#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dwRtoAlgorithm; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwNumConns; int /*<<< orphan*/  dwOutRsts; int /*<<< orphan*/  dwInErrs; int /*<<< orphan*/  dwRetransSegs; int /*<<< orphan*/  dwOutSegs; int /*<<< orphan*/  dwInSegs; int /*<<< orphan*/  dwCurrEstab; int /*<<< orphan*/  dwEstabResets; int /*<<< orphan*/  dwAttemptFails; int /*<<< orphan*/  dwPassiveOpens; int /*<<< orphan*/  dwActiveOpens; int /*<<< orphan*/  dwMaxConn; int /*<<< orphan*/  dwRtoMax; int /*<<< orphan*/  dwRtoMin; } ;
typedef  TYPE_1__ MIB_TCPSTATS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ NO_ERROR ; 
 TYPE_3__ U (TYPE_1__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pGetTcpStatistics (TYPE_1__*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,...) ; 
 int winetest_debug ; 

__attribute__((used)) static void testGetTcpStatistics(void)
{
  if (pGetTcpStatistics) {
    DWORD apiReturn;
    MIB_TCPSTATS stats;

    apiReturn = pGetTcpStatistics(NULL);
    if (apiReturn == ERROR_NOT_SUPPORTED) {
      skip("GetTcpStatistics is not supported\n");
      return;
    }
    ok(apiReturn == ERROR_INVALID_PARAMETER,
     "GetTcpStatistics(NULL) returned %d, expected ERROR_INVALID_PARAMETER\n",
     apiReturn);
    apiReturn = pGetTcpStatistics(&stats);
    ok(apiReturn == NO_ERROR,
      "GetTcpStatistics returned %d, expected NO_ERROR\n", apiReturn);
    if (apiReturn == NO_ERROR && winetest_debug > 1)
    {
        trace( "TCP stats:\n" );
        trace( "    dwRtoAlgorithm: %u\n", U(stats).dwRtoAlgorithm );
        trace( "    dwRtoMin:       %u\n", stats.dwRtoMin );
        trace( "    dwRtoMax:       %u\n", stats.dwRtoMax );
        trace( "    dwMaxConn:      %u\n", stats.dwMaxConn );
        trace( "    dwActiveOpens:  %u\n", stats.dwActiveOpens );
        trace( "    dwPassiveOpens: %u\n", stats.dwPassiveOpens );
        trace( "    dwAttemptFails: %u\n", stats.dwAttemptFails );
        trace( "    dwEstabResets:  %u\n", stats.dwEstabResets );
        trace( "    dwCurrEstab:    %u\n", stats.dwCurrEstab );
        trace( "    dwInSegs:       %u\n", stats.dwInSegs );
        trace( "    dwOutSegs:      %u\n", stats.dwOutSegs );
        trace( "    dwRetransSegs:  %u\n", stats.dwRetransSegs );
        trace( "    dwInErrs:       %u\n", stats.dwInErrs );
        trace( "    dwOutRsts:      %u\n", stats.dwOutRsts );
        trace( "    dwNumConns:     %u\n", stats.dwNumConns );
    }
  }
}