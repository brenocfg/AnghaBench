#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int ULONG ;
struct TYPE_9__ {int s_addr; } ;
struct TYPE_10__ {TYPE_1__ sin_addr; } ;
struct TYPE_14__ {TYPE_2__ AddressIn; } ;
struct TYPE_13__ {int iiFlags; TYPE_6__ iiNetmask; TYPE_6__ iiBroadcastAddress; TYPE_6__ iiAddress; } ;
struct TYPE_12__ {int dwAddr; int wType; int dwBCastAddr; int dwMask; } ;
struct TYPE_11__ {int dwNumEntries; TYPE_4__* table; } ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_3__* PMIB_IPADDRTABLE ;
typedef  TYPE_4__* PMIB_IPADDRROW ;
typedef  TYPE_5__* LPINTERFACE_INFO ;
typedef  int /*<<< orphan*/  INTERFACE_INFO ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IFF_BROADCAST ; 
 int IFF_LOOPBACK ; 
 int IFF_MULTICAST ; 
 int IFF_UP ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int MIB_IPADDR_DISCONNECTED ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  SIO_GET_INTERFACE_LIST ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  Test_WSAIoctl_InitTest (TYPE_3__**) ; 
 int /*<<< orphan*/  WSACleanup () ; 
 scalar_t__ WSAEFAULT ; 
 scalar_t__ WSAGetLastError () ; 
 int WSAIoctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WSASocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  ok_dec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_hex (int,int) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,...) ; 
 int /*<<< orphan*/  traceaddr (char*,TYPE_6__) ; 
 int winetest_debug ; 

void Test_WSAIoctl_GetInterfaceList()
{
    WSADATA wdata;
    INT iResult;
    SOCKET sck;
    ULONG buflen, BytesReturned, BCastAddr;
    ULONG infoCount, i1, j1, iiFlagsExpected;
    BYTE* buf = NULL;
    LPINTERFACE_INFO ifInfo;
    PMIB_IPADDRTABLE pTable = NULL;
    PMIB_IPADDRROW pRow;

    /* Get PMIB_IPADDRTABE - these results we should get from wshtcpip.dll too. */ 
    /* pTable is allocated by Test_WSAIoctl_InitTest! */
    if (!Test_WSAIoctl_InitTest(&pTable))
        goto cleanup;

    /* Start up Winsock */
    iResult = WSAStartup(MAKEWORD(2, 2), &wdata);
    ok(iResult == 0, "WSAStartup failed. iResult = %d\n", iResult);

    /* Create the socket */
    sck = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, 0, 0, 0);
    ok(sck != INVALID_SOCKET, "WSASocket failed. sck = %d\n", (INT)sck);
    if (sck == INVALID_SOCKET)
    {
        skip("Failed to create socket!\n");
        goto cleanup;
    }

    /* Do the Ioctl (buffer to small) */
    buflen = sizeof(INTERFACE_INFO)-1;
    buf = (BYTE*)HeapAlloc(GetProcessHeap(), 0, buflen);
    if (buf == NULL)
    {
        skip("Failed to allocate memory!\n");
        goto cleanup;
    }
    BytesReturned = 0;
    iResult = WSAIoctl(sck, SIO_GET_INTERFACE_LIST, 0, 0,
                       buf, buflen, &BytesReturned, 0, 0);
    ok(iResult == -1, "WSAIoctl/SIO_GET_INTERFACE_LIST did not fail! iResult = %d.\n", iResult);
    ok_hex(WSAGetLastError(), WSAEFAULT);
    ok(BytesReturned == 0, "WSAIoctl/SIO_GET_INTERFACE_LIST: BytesReturned should be 0, not %ld.\n", BytesReturned);
    HeapFree(GetProcessHeap(), 0, buf);
    buf = NULL;

    /* Do the Ioctl 
       In most cases no loop is done. 
       Only if WSAIoctl fails with WSAEFAULT (buffer to small) we need to retry with a 
       larger buffer */
    i1 = 0;
    while (TRUE) 
    {
        if (buf != NULL)
        {
            HeapFree(GetProcessHeap(), 0, buf);
            buf = NULL;
        }

        buflen = sizeof(INTERFACE_INFO) * (i1+1) * 32;
        buf = (BYTE*)HeapAlloc(GetProcessHeap(), 0, buflen);
        if (buf == NULL)
        {
            skip("Failed to allocate memory!\n");
            goto cleanup;
        }
        BytesReturned = 0;
        iResult = WSAIoctl(sck, SIO_GET_INTERFACE_LIST, 0, 0,
                           buf, buflen, &BytesReturned, 0, 0);
        /* we have what we want ... leave loop */
        if (iResult == NO_ERROR)
            break;
        /* only retry if buffer was to small */
        /* to avoid infinite loop we maximum retry count is 4 */
        if ((i1 >= 4) || (WSAGetLastError() != WSAEFAULT))
        {
            ok_hex(iResult, NO_ERROR);
            skip("WSAIoctl / SIO_GET_INTERFACE_LIST\n");
            goto cleanup;
        }
        /* buffer to small -> retry */
        i1++;
    }

    ok_dec(BytesReturned % sizeof(INTERFACE_INFO), 0);

    /* Calculate how many INTERFACE_INFO we got */
    infoCount = BytesReturned / sizeof(INTERFACE_INFO);
    ok(infoCount == pTable->dwNumEntries, 
       "Wrong count of entries! Got %ld, expected %ld.\n", pTable->dwNumEntries, infoCount);    

    if (winetest_debug >= 2)
    {
        trace("WSAIoctl\n");
        trace("  BytesReturned %ld - InfoCount %ld\n ", BytesReturned, infoCount);
        ifInfo = (LPINTERFACE_INFO)buf;
        for (i1 = 0; i1 < infoCount; i1++)
        {
            trace("entry-index %ld\n", i1);
            trace("  iiFlags %ld\n", ifInfo->iiFlags);
            traceaddr("ifInfo^.iiAddress", ifInfo->iiAddress);
            traceaddr("ifInfo^.iiBroadcastAddress", ifInfo->iiBroadcastAddress);
            traceaddr("ifInfo^.iiNetmask", ifInfo->iiNetmask);
            ifInfo++;
        }
    }

    /* compare entries */
    ifInfo = (LPINTERFACE_INFO)buf;
    for (i1 = 0; i1 < infoCount; i1++)
    {
        if (winetest_debug >= 2)
            trace("Entry %ld\n", i1);
        for (j1 = 0; j1 < pTable->dwNumEntries; j1++)
        {
            if (ifInfo[i1].iiAddress.AddressIn.sin_addr.s_addr == pTable->table[j1].dwAddr)
            {
                pRow = &pTable->table[j1];
                break;
            }
        }
        if (j1 == pTable->dwNumEntries)
        {
            skip("Skipping interface\n");
            continue;
        }

        /* iiFlags
         * Don't know if this value is fix for SIO_GET_INTERFACE_LIST! */ 
        iiFlagsExpected = IFF_BROADCAST | IFF_MULTICAST;
        if ((pRow->wType & MIB_IPADDR_DISCONNECTED) == 0)
            iiFlagsExpected |= IFF_UP;
        if (pRow->dwAddr == ntohl(INADDR_LOOPBACK))
        {
            iiFlagsExpected |= IFF_LOOPBACK;
            /* on Windows 7 loopback has broadcast flag cleared */
            //iiFlagsExpected &= ~IFF_BROADCAST;
        }
        
        ok_hex(ifInfo[i1].iiFlags, iiFlagsExpected);
        ok_hex(ifInfo[i1].iiAddress.AddressIn.sin_addr.s_addr, pRow->dwAddr);
        // dwBCastAddr is not the "real" Broadcast-Address. 
        BCastAddr = (pRow->dwBCastAddr == 1 && (iiFlagsExpected & IFF_BROADCAST) != 0) ? 0xFFFFFFFF : 0x0;
        ok_hex(ifInfo[i1].iiBroadcastAddress.AddressIn.sin_addr.s_addr, BCastAddr);
        ok_hex(ifInfo[i1].iiNetmask.AddressIn.sin_addr.s_addr, pRow->dwMask);
    }

cleanup:
    if (sck != 0)
        closesocket(sck);
    if (pTable != NULL)
       free(pTable);
    if (buf != NULL)
       HeapFree(GetProcessHeap(), 0, buf);
    WSACleanup();
}