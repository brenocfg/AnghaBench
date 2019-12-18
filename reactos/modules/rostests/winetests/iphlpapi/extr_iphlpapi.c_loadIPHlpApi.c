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
 scalar_t__ GetProcAddress (scalar_t__,char*) ; 
 scalar_t__ LoadLibraryA (char*) ; 
 scalar_t__ hLibrary ; 
 void* pCancelIPChangeNotify ; 
 void* pConvertInterfaceGuidToLuid ; 
 void* pConvertInterfaceIndexToLuid ; 
 void* pConvertInterfaceLuidToGuid ; 
 void* pConvertInterfaceLuidToIndex ; 
 void* pConvertInterfaceLuidToNameA ; 
 void* pConvertInterfaceLuidToNameW ; 
 void* pConvertInterfaceNameToLuidA ; 
 void* pConvertInterfaceNameToLuidW ; 
 void* pCreateSortedAddressPairs ; 
 void* pFreeMibTable ; 
 void* pGetAdaptersAddresses ; 
 void* pGetAdaptersInfo ; 
 void* pGetExtendedTcpTable ; 
 void* pGetExtendedUdpTable ; 
 void* pGetFriendlyIfIndex ; 
 void* pGetIcmpStatistics ; 
 void* pGetIcmpStatisticsEx ; 
 void* pGetIfEntry ; 
 void* pGetIfEntry2 ; 
 void* pGetIfTable ; 
 void* pGetIfTable2 ; 
 void* pGetInterfaceInfo ; 
 void* pGetIpAddrTable ; 
 void* pGetIpForwardTable ; 
 void* pGetIpNetTable ; 
 void* pGetIpStatistics ; 
 void* pGetIpStatisticsEx ; 
 void* pGetNetworkParams ; 
 void* pGetNumberOfInterfaces ; 
 void* pGetPerAdapterInfo ; 
 void* pGetTcpStatistics ; 
 void* pGetTcpStatisticsEx ; 
 void* pGetTcpTable ; 
 void* pGetUdpStatistics ; 
 void* pGetUdpStatisticsEx ; 
 void* pGetUdpTable ; 
 void* pIcmpCreateFile ; 
 void* pIcmpSendEcho ; 
 void* pNotifyAddrChange ; 
 void* pSetTcpEntry ; 

__attribute__((used)) static void loadIPHlpApi(void)
{
  hLibrary = LoadLibraryA("iphlpapi.dll");
  if (hLibrary) {
    pGetNumberOfInterfaces = (void *)GetProcAddress(hLibrary, "GetNumberOfInterfaces");
    pGetIpAddrTable = (void *)GetProcAddress(hLibrary, "GetIpAddrTable");
    pGetIfEntry = (void *)GetProcAddress(hLibrary, "GetIfEntry");
    pGetIfEntry2 = (void *)GetProcAddress(hLibrary, "GetIfEntry2");
    pGetFriendlyIfIndex = (void *)GetProcAddress(hLibrary, "GetFriendlyIfIndex");
    pGetIfTable = (void *)GetProcAddress(hLibrary, "GetIfTable");
    pGetIfTable2 = (void *)GetProcAddress(hLibrary, "GetIfTable2");
    pGetIpForwardTable = (void *)GetProcAddress(hLibrary, "GetIpForwardTable");
    pGetIpNetTable = (void *)GetProcAddress(hLibrary, "GetIpNetTable");
    pGetInterfaceInfo = (void *)GetProcAddress(hLibrary, "GetInterfaceInfo");
    pGetAdaptersInfo = (void *)GetProcAddress(hLibrary, "GetAdaptersInfo");
    pGetNetworkParams = (void *)GetProcAddress(hLibrary, "GetNetworkParams");
    pGetIcmpStatistics = (void *)GetProcAddress(hLibrary, "GetIcmpStatistics");
    pGetIpStatistics = (void *)GetProcAddress(hLibrary, "GetIpStatistics");
    pGetTcpStatistics = (void *)GetProcAddress(hLibrary, "GetTcpStatistics");
    pGetUdpStatistics = (void *)GetProcAddress(hLibrary, "GetUdpStatistics");
    pGetIcmpStatisticsEx = (void *)GetProcAddress(hLibrary, "GetIcmpStatisticsEx");
    pGetIpStatisticsEx = (void *)GetProcAddress(hLibrary, "GetIpStatisticsEx");
    pGetTcpStatisticsEx = (void *)GetProcAddress(hLibrary, "GetTcpStatisticsEx");
    pGetUdpStatisticsEx = (void *)GetProcAddress(hLibrary, "GetUdpStatisticsEx");
    pGetTcpTable = (void *)GetProcAddress(hLibrary, "GetTcpTable");
    pGetUdpTable = (void *)GetProcAddress(hLibrary, "GetUdpTable");
    pGetPerAdapterInfo = (void *)GetProcAddress(hLibrary, "GetPerAdapterInfo");
    pGetAdaptersAddresses = (void *)GetProcAddress(hLibrary, "GetAdaptersAddresses");
    pNotifyAddrChange = (void *)GetProcAddress(hLibrary, "NotifyAddrChange");
    pCancelIPChangeNotify = (void *)GetProcAddress(hLibrary, "CancelIPChangeNotify");
    pGetExtendedTcpTable = (void *)GetProcAddress(hLibrary, "GetExtendedTcpTable");
    pGetExtendedUdpTable = (void *)GetProcAddress(hLibrary, "GetExtendedUdpTable");
    pSetTcpEntry = (void *)GetProcAddress(hLibrary, "SetTcpEntry");
    pIcmpCreateFile = (void *)GetProcAddress(hLibrary, "IcmpCreateFile");
    pIcmpSendEcho = (void *)GetProcAddress(hLibrary, "IcmpSendEcho");
    pCreateSortedAddressPairs = (void *)GetProcAddress(hLibrary, "CreateSortedAddressPairs");
    pFreeMibTable = (void *)GetProcAddress(hLibrary, "FreeMibTable");
    pConvertInterfaceGuidToLuid = (void *)GetProcAddress(hLibrary, "ConvertInterfaceGuidToLuid");
    pConvertInterfaceIndexToLuid = (void *)GetProcAddress(hLibrary, "ConvertInterfaceIndexToLuid");
    pConvertInterfaceLuidToGuid = (void *)GetProcAddress(hLibrary, "ConvertInterfaceLuidToGuid");
    pConvertInterfaceLuidToIndex = (void *)GetProcAddress(hLibrary, "ConvertInterfaceLuidToIndex");
    pConvertInterfaceLuidToNameA = (void *)GetProcAddress(hLibrary, "ConvertInterfaceLuidToNameA");
    pConvertInterfaceLuidToNameW = (void *)GetProcAddress(hLibrary, "ConvertInterfaceLuidToNameW");
    pConvertInterfaceNameToLuidA = (void *)GetProcAddress(hLibrary, "ConvertInterfaceNameToLuidA");
    pConvertInterfaceNameToLuidW = (void *)GetProcAddress(hLibrary, "ConvertInterfaceNameToLuidW");
  }
}