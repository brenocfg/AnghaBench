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

/* Variables and functions */
 int /*<<< orphan*/  testGetIcmpStatistics () ; 
 int /*<<< orphan*/  testGetIcmpStatisticsEx () ; 
 int /*<<< orphan*/  testGetIfTable () ; 
 int /*<<< orphan*/  testGetIpAddrTable () ; 
 int /*<<< orphan*/  testGetIpForwardTable () ; 
 int /*<<< orphan*/  testGetIpNetTable () ; 
 int /*<<< orphan*/  testGetIpStatistics () ; 
 int /*<<< orphan*/  testGetIpStatisticsEx () ; 
 int /*<<< orphan*/  testGetNumberOfInterfaces () ; 
 int /*<<< orphan*/  testGetTcpStatistics () ; 
 int /*<<< orphan*/  testGetTcpStatisticsEx () ; 
 int /*<<< orphan*/  testGetTcpTable () ; 
 int /*<<< orphan*/  testGetUdpStatistics () ; 
 int /*<<< orphan*/  testGetUdpStatisticsEx () ; 
 int /*<<< orphan*/  testGetUdpTable () ; 
 int /*<<< orphan*/  testIcmpSendEcho () ; 
 int /*<<< orphan*/  testSetTcpEntry () ; 

__attribute__((used)) static void testWinNT4Functions(void)
{
  testGetNumberOfInterfaces();
  testGetIpAddrTable();
  testGetIfTable();
  testGetIpForwardTable();
  testGetIpNetTable();
  testGetIcmpStatistics();
  testGetIpStatistics();
  testGetTcpStatistics();
  testGetUdpStatistics();
  testGetIcmpStatisticsEx();
  testGetIpStatisticsEx();
  testGetTcpStatisticsEx();
  testGetUdpStatisticsEx();
  testGetTcpTable();
  testGetUdpTable();
  testSetTcpEntry();
  testIcmpSendEcho();
}