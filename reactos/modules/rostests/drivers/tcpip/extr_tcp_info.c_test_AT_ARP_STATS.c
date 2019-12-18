#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  S_addr; } ;
struct in_addr {TYPE_2__ S_un; } ;
typedef  scalar_t__ ULONG ;
struct TYPE_14__ {scalar_t__ ai_numroutes; scalar_t__ ai_unknown; scalar_t__ ae_index; scalar_t__ ae_unknown; int /*<<< orphan*/  ae_address; int /*<<< orphan*/  ae_physaddrlen; int /*<<< orphan*/  ae_physaddr; } ;
struct TYPE_11__ {int /*<<< orphan*/  toi_id; int /*<<< orphan*/  toi_type; int /*<<< orphan*/  toi_class; int /*<<< orphan*/  toi_entity; } ;
struct TYPE_13__ {TYPE_1__ ID; } ;
typedef  int /*<<< orphan*/  TDIEntityID ;
typedef  TYPE_3__ TCP_REQUEST_QUERY_INFORMATION_EX ;
typedef  int /*<<< orphan*/  Request ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ArpInfo ;
typedef  int /*<<< orphan*/  ArpEntries ;
typedef  TYPE_4__ ARPInfo ;
typedef  TYPE_4__ ARPEntry ;

/* Variables and functions */
 scalar_t__ AT_ARP ; 
 int /*<<< orphan*/  AT_MIB_ADDRXLAT_ENTRY_ID ; 
 int /*<<< orphan*/  AT_MIB_ADDRXLAT_INFO_ID ; 
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int,TYPE_4__*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  INFO_CLASS_PROTOCOL ; 
 int /*<<< orphan*/  INFO_TYPE_PROVIDER ; 
 int /*<<< orphan*/  IOCTL_TCP_QUERY_INFORMATION_EX ; 
 int /*<<< orphan*/  IndentationLevel ; 
 int /*<<< orphan*/  RtlIpv4AddressToStringA (struct in_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpFileHandle ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 
 scalar_t__ dbg_print_physaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indent_printf (char*,...) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_long (scalar_t__,int) ; 

__attribute__((used)) static
void
test_AT_ARP_STATS(
    TDIEntityID Id,
    ULONG EntityType)
{
    ARPInfo ArpInfo;
    TCP_REQUEST_QUERY_INFORMATION_EX Request;
    ULONG BufferSize = 0;
    BOOL Result;

    /* Not valid for other entity types */
    if (EntityType != AT_ARP)
        return;

    ZeroMemory(&Request, sizeof(Request));
    Request.ID.toi_entity = Id;
    Request.ID.toi_class = INFO_CLASS_PROTOCOL;
    Request.ID.toi_type = INFO_TYPE_PROVIDER;
    Request.ID.toi_id = AT_MIB_ADDRXLAT_INFO_ID;

    Result = DeviceIoControl(
        TcpFileHandle,
        IOCTL_TCP_QUERY_INFORMATION_EX,
        &Request,
        sizeof(Request),
        &ArpInfo,
        sizeof(ArpInfo),
        &BufferSize,
        NULL);
    ok(Result, "DeviceIoControl failed.\n");
    ok_long(BufferSize, sizeof(ArpInfo));

    indent_printf("ARP Info:\n");
    IndentationLevel++;

    indent_printf("ai_numroutes: %lu\n", ArpInfo.ai_numroutes);
    indent_printf("ai_unknown:   %lx\n", ArpInfo.ai_unknown);

    if (ArpInfo.ai_numroutes)
    {
        ARPEntry* ArpEntries;
        ULONG i;

        Request.ID.toi_id = AT_MIB_ADDRXLAT_ENTRY_ID;

        ArpEntries = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ArpInfo.ai_numroutes * sizeof(ArpEntries[0]));
        ok(ArpEntries != NULL, "\n");

        Result = DeviceIoControl(
            TcpFileHandle,
            IOCTL_TCP_QUERY_INFORMATION_EX,
            &Request,
            sizeof(Request),
            ArpEntries,
            ArpInfo.ai_numroutes * sizeof(ArpEntries[0]),
            &BufferSize,
            NULL);
        ok(Result, "DeviceIoControl failed.\n");
        ok_long(BufferSize, ArpInfo.ai_numroutes * sizeof(ArpEntries[0]));

        for (i = 0; i < ArpInfo.ai_numroutes; i++)
        {
            CHAR AddressString[16];
            struct in_addr Addr;

            Addr.S_un.S_addr = ArpEntries[i].ae_address;
            RtlIpv4AddressToStringA(&Addr, AddressString);

            indent_printf("ARP Entry %lu:\n", i);

            IndentationLevel++;

            indent_printf("ae_index:    %lu\n", ArpEntries[i].ae_index);
            indent_printf("ae_physaddr: %s\n", dbg_print_physaddr(ArpEntries[i].ae_physaddr, ArpEntries[i].ae_physaddrlen));
            indent_printf("ae_address:  %lx (%s)\n", ArpEntries[i].ae_address, AddressString);
            indent_printf("ae_unknown:  %lu.\n", ArpEntries[i].ae_unknown);

            IndentationLevel--;
        }

        HeapFree(GetProcessHeap(), 0, ArpEntries);
    }

    IndentationLevel--;
}