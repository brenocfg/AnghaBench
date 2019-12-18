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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* dwMsgs; char* dwErrors; char* dwDestUnreachs; char* dwTimeExcds; char* dwParmProbs; char* dwSrcQuenchs; char* dwRedirects; char* dwEchos; char* dwEchoReps; char* dwTimestamps; char* dwTimestampReps; char* dwAddrMasks; char* dwAddrMaskReps; } ;
struct TYPE_6__ {char* dwMsgs; char* dwErrors; char* dwDestUnreachs; char* dwTimeExcds; char* dwParmProbs; char* dwSrcQuenchs; char* dwRedirects; char* dwEchos; char* dwEchoReps; char* dwTimestamps; char* dwTimestampReps; char* dwAddrMasks; char* dwAddrMaskReps; } ;
struct TYPE_8__ {TYPE_2__ icmpOutStats; TYPE_1__ icmpInStats; } ;
struct TYPE_9__ {TYPE_3__ stats; } ;
typedef  TYPE_4__ MIB_ICMP ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pGetIcmpStatistics (TYPE_4__*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,char*,char*) ; 
 int winetest_debug ; 

__attribute__((used)) static void testGetIcmpStatistics(void)
{
  if (pGetIcmpStatistics) {
    DWORD apiReturn;
    MIB_ICMP stats;

    /* Crashes on Vista */
    if (0) {
      apiReturn = pGetIcmpStatistics(NULL);
      if (apiReturn == ERROR_NOT_SUPPORTED)
        return;
      ok(apiReturn == ERROR_INVALID_PARAMETER,
       "GetIcmpStatistics(NULL) returned %d, expected ERROR_INVALID_PARAMETER\n",
       apiReturn);
    }

    apiReturn = pGetIcmpStatistics(&stats);
    if (apiReturn == ERROR_NOT_SUPPORTED)
    {
      skip("GetIcmpStatistics is not supported\n");
      return;
    }
    ok(apiReturn == NO_ERROR,
     "GetIcmpStatistics returned %d, expected NO_ERROR\n", apiReturn);
    if (apiReturn == NO_ERROR && winetest_debug > 1)
    {
        trace( "ICMP stats:          %8s %8s\n", "in", "out" );
        trace( "    dwMsgs:          %8u %8u\n", stats.stats.icmpInStats.dwMsgs, stats.stats.icmpOutStats.dwMsgs );
        trace( "    dwErrors:        %8u %8u\n", stats.stats.icmpInStats.dwErrors, stats.stats.icmpOutStats.dwErrors );
        trace( "    dwDestUnreachs:  %8u %8u\n", stats.stats.icmpInStats.dwDestUnreachs, stats.stats.icmpOutStats.dwDestUnreachs );
        trace( "    dwTimeExcds:     %8u %8u\n", stats.stats.icmpInStats.dwTimeExcds, stats.stats.icmpOutStats.dwTimeExcds );
        trace( "    dwParmProbs:     %8u %8u\n", stats.stats.icmpInStats.dwParmProbs, stats.stats.icmpOutStats.dwParmProbs );
        trace( "    dwSrcQuenchs:    %8u %8u\n", stats.stats.icmpInStats.dwSrcQuenchs, stats.stats.icmpOutStats.dwSrcQuenchs );
        trace( "    dwRedirects:     %8u %8u\n", stats.stats.icmpInStats.dwRedirects, stats.stats.icmpOutStats.dwRedirects );
        trace( "    dwEchos:         %8u %8u\n", stats.stats.icmpInStats.dwEchos, stats.stats.icmpOutStats.dwEchos );
        trace( "    dwEchoReps:      %8u %8u\n", stats.stats.icmpInStats.dwEchoReps, stats.stats.icmpOutStats.dwEchoReps );
        trace( "    dwTimestamps:    %8u %8u\n", stats.stats.icmpInStats.dwTimestamps, stats.stats.icmpOutStats.dwTimestamps );
        trace( "    dwTimestampReps: %8u %8u\n", stats.stats.icmpInStats.dwTimestampReps, stats.stats.icmpOutStats.dwTimestampReps );
        trace( "    dwAddrMasks:     %8u %8u\n", stats.stats.icmpInStats.dwAddrMasks, stats.stats.icmpOutStats.dwAddrMasks );
        trace( "    dwAddrMaskReps:  %8u %8u\n", stats.stats.icmpInStats.dwAddrMaskReps, stats.stats.icmpOutStats.dwAddrMaskReps );
    }
  }
}