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
struct TYPE_6__ {int /*<<< orphan*/  dwForwarding; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwNumRoutes; int /*<<< orphan*/  dwNumAddr; int /*<<< orphan*/  dwNumIf; int /*<<< orphan*/  dwFragCreates; int /*<<< orphan*/  dwFragFails; int /*<<< orphan*/  dwFragOks; int /*<<< orphan*/  dwReasmFails; int /*<<< orphan*/  dwReasmOks; int /*<<< orphan*/  dwReasmReqds; int /*<<< orphan*/  dwReasmTimeout; int /*<<< orphan*/  dwOutNoRoutes; int /*<<< orphan*/  dwOutDiscards; int /*<<< orphan*/  dwRoutingDiscards; int /*<<< orphan*/  dwOutRequests; int /*<<< orphan*/  dwInDelivers; int /*<<< orphan*/  dwInDiscards; int /*<<< orphan*/  dwInUnknownProtos; int /*<<< orphan*/  dwForwDatagrams; int /*<<< orphan*/  dwInAddrErrors; int /*<<< orphan*/  dwInHdrErrors; int /*<<< orphan*/  dwInReceives; int /*<<< orphan*/  dwDefaultTTL; } ;
typedef  TYPE_1__ MIB_IPSTATS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ NO_ERROR ; 
 TYPE_3__ U (TYPE_1__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pGetIpStatistics (TYPE_1__*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,...) ; 
 int winetest_debug ; 

__attribute__((used)) static void testGetIpStatistics(void)
{
  if (pGetIpStatistics) {
    DWORD apiReturn;
    MIB_IPSTATS stats;

    apiReturn = pGetIpStatistics(NULL);
    if (apiReturn == ERROR_NOT_SUPPORTED) {
      skip("GetIpStatistics is not supported\n");
      return;
    }
    ok(apiReturn == ERROR_INVALID_PARAMETER,
     "GetIpStatistics(NULL) returned %d, expected ERROR_INVALID_PARAMETER\n",
     apiReturn);
    apiReturn = pGetIpStatistics(&stats);
    ok(apiReturn == NO_ERROR,
      "GetIpStatistics returned %d, expected NO_ERROR\n", apiReturn);
    if (apiReturn == NO_ERROR && winetest_debug > 1)
    {
        trace( "IP stats:\n" );
        trace( "    dwForwarding:      %u\n", U(stats).dwForwarding );
        trace( "    dwDefaultTTL:      %u\n", stats.dwDefaultTTL );
        trace( "    dwInReceives:      %u\n", stats.dwInReceives );
        trace( "    dwInHdrErrors:     %u\n", stats.dwInHdrErrors );
        trace( "    dwInAddrErrors:    %u\n", stats.dwInAddrErrors );
        trace( "    dwForwDatagrams:   %u\n", stats.dwForwDatagrams );
        trace( "    dwInUnknownProtos: %u\n", stats.dwInUnknownProtos );
        trace( "    dwInDiscards:      %u\n", stats.dwInDiscards );
        trace( "    dwInDelivers:      %u\n", stats.dwInDelivers );
        trace( "    dwOutRequests:     %u\n", stats.dwOutRequests );
        trace( "    dwRoutingDiscards: %u\n", stats.dwRoutingDiscards );
        trace( "    dwOutDiscards:     %u\n", stats.dwOutDiscards );
        trace( "    dwOutNoRoutes:     %u\n", stats.dwOutNoRoutes );
        trace( "    dwReasmTimeout:    %u\n", stats.dwReasmTimeout );
        trace( "    dwReasmReqds:      %u\n", stats.dwReasmReqds );
        trace( "    dwReasmOks:        %u\n", stats.dwReasmOks );
        trace( "    dwReasmFails:      %u\n", stats.dwReasmFails );
        trace( "    dwFragOks:         %u\n", stats.dwFragOks );
        trace( "    dwFragFails:       %u\n", stats.dwFragFails );
        trace( "    dwFragCreates:     %u\n", stats.dwFragCreates );
        trace( "    dwNumIf:           %u\n", stats.dwNumIf );
        trace( "    dwNumAddr:         %u\n", stats.dwNumAddr );
        trace( "    dwNumRoutes:       %u\n", stats.dwNumRoutes );
    }
  }
}