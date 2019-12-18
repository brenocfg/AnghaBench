#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dwNumAddrs; int /*<<< orphan*/  dwOutDatagrams; int /*<<< orphan*/  dwInErrors; int /*<<< orphan*/  dwNoPorts; int /*<<< orphan*/  dwInDatagrams; } ;
typedef  TYPE_1__ MIB_UDPSTATS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BAN ; 
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ NO_ERROR ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pGetUdpStatisticsEx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int winetest_debug ; 

__attribute__((used)) static void testGetUdpStatisticsEx(void)
{
    DWORD apiReturn;
    MIB_UDPSTATS stats;

    if (!pGetUdpStatisticsEx)
    {
        win_skip( "GetUdpStatisticsEx not available\n" );
        return;
    }

    apiReturn = pGetUdpStatisticsEx(NULL, AF_INET);
    ok(apiReturn == ERROR_INVALID_PARAMETER,
       "GetUdpStatisticsEx(NULL, AF_INET); returned %d, expected ERROR_INVALID_PARAMETER\n", apiReturn);

    apiReturn = pGetUdpStatisticsEx(&stats, AF_BAN);
    ok(apiReturn == ERROR_INVALID_PARAMETER || apiReturn == ERROR_NOT_SUPPORTED,
       "GetUdpStatisticsEx(&stats, AF_BAN) returned %d, expected ERROR_INVALID_PARAMETER\n", apiReturn);

    apiReturn = pGetUdpStatisticsEx(&stats, AF_INET);
    ok(apiReturn == NO_ERROR, "GetUdpStatisticsEx returned %d, expected NO_ERROR\n", apiReturn);
    if (apiReturn == NO_ERROR && winetest_debug > 1)
    {
        trace( "UDP IPv4 Ex stats:\n" );
        trace( "    dwInDatagrams:  %u\n", stats.dwInDatagrams );
        trace( "    dwNoPorts:      %u\n", stats.dwNoPorts );
        trace( "    dwInErrors:     %u\n", stats.dwInErrors );
        trace( "    dwOutDatagrams: %u\n", stats.dwOutDatagrams );
        trace( "    dwNumAddrs:     %u\n", stats.dwNumAddrs );
    }

    apiReturn = pGetUdpStatisticsEx(&stats, AF_INET6);
    ok(apiReturn == NO_ERROR || broken(apiReturn == ERROR_NOT_SUPPORTED),
       "GetUdpStatisticsEx returned %d, expected NO_ERROR\n", apiReturn);
    if (apiReturn == NO_ERROR && winetest_debug > 1)
    {
        trace( "UDP IPv6 Ex stats:\n" );
        trace( "    dwInDatagrams:  %u\n", stats.dwInDatagrams );
        trace( "    dwNoPorts:      %u\n", stats.dwNoPorts );
        trace( "    dwInErrors:     %u\n", stats.dwInErrors );
        trace( "    dwOutDatagrams: %u\n", stats.dwOutDatagrams );
        trace( "    dwNumAddrs:     %u\n", stats.dwNumAddrs );
    }
}