#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ S_addr; } ;
struct in_addr {TYPE_1__ S_un; } ;
typedef  scalar_t__ ULONG ;
struct TYPE_14__ {int /*<<< orphan*/  toi_id; void* toi_type; void* toi_class; void* toi_entity; } ;
struct TYPE_15__ {scalar_t__ ipsi_forwarding; scalar_t__ ipsi_defaultttl; scalar_t__ ipsi_inreceives; scalar_t__ ipsi_inhdrerrors; scalar_t__ ipsi_inaddrerrors; scalar_t__ ipsi_forwdatagrams; scalar_t__ ipsi_inunknownprotos; scalar_t__ ipsi_indiscards; scalar_t__ ipsi_indelivers; scalar_t__ ipsi_outrequests; scalar_t__ ipsi_routingdiscards; scalar_t__ ipsi_outdiscards; scalar_t__ ipsi_outnoroutes; scalar_t__ ipsi_reasmtimeout; scalar_t__ ipsi_reasmreqds; scalar_t__ ipsi_reasmoks; scalar_t__ ipsi_reasmfails; scalar_t__ ipsi_fragoks; scalar_t__ ipsi_fragfails; scalar_t__ ipsi_fragcreates; scalar_t__ ipsi_numif; scalar_t__ ipsi_numaddr; scalar_t__ ipsi_numroutes; scalar_t__ iae_addr; scalar_t__ iae_index; scalar_t__ iae_mask; scalar_t__ iae_bcastaddr; scalar_t__ iae_reasmsize; scalar_t__ iae_context; scalar_t__* Context; scalar_t__ iii_flags; scalar_t__ iii_mtu; scalar_t__ iii_speed; scalar_t__ ire_dest; scalar_t__ ire_index; scalar_t__ ire_metric1; scalar_t__ ire_metric2; scalar_t__ ire_metric3; scalar_t__ ire_metric4; scalar_t__ ire_nexthop; scalar_t__ ire_type; scalar_t__ ire_proto; scalar_t__ ire_age; scalar_t__ ire_mask; scalar_t__ ire_metric5; scalar_t__ ire_context; TYPE_2__ ID; int /*<<< orphan*/  iii_addrlength; int /*<<< orphan*/  iii_addr; } ;
typedef  void* TDIEntityID ;
typedef  TYPE_3__ TCP_REQUEST_QUERY_INFORMATION_EX ;
typedef  int /*<<< orphan*/  RouteEntries ;
typedef  int /*<<< orphan*/  Request ;
typedef  int /*<<< orphan*/  IpSnmpInfo ;
typedef  TYPE_3__ IPSNMPInfo ;
typedef  TYPE_3__ IPRouteEntry ;
typedef  TYPE_3__ IPInterfaceInfo ;
typedef  TYPE_3__ IPAddrEntry ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  AddrEntries ;

/* Variables and functions */
 scalar_t__ CL_NL_IP ; 
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int,TYPE_3__*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 void* INFO_CLASS_PROTOCOL ; 
 void* INFO_TYPE_PROVIDER ; 
 int /*<<< orphan*/  IOCTL_TCP_QUERY_INFORMATION_EX ; 
 int /*<<< orphan*/  IP_INTFC_INFO_ID ; 
 int /*<<< orphan*/  IP_MIB_ADDRTABLE_ENTRY_ID ; 
 int /*<<< orphan*/  IP_MIB_ARPTABLE_ENTRY_ID ; 
 int /*<<< orphan*/  IP_MIB_STATS_ID ; 
 int /*<<< orphan*/  IndentationLevel ; 
 scalar_t__ MAX_PHYSADDR_SIZE ; 
 int /*<<< orphan*/  RtlIpv4AddressToStringA (struct in_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpFileHandle ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 
 scalar_t__ dbg_print_physaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indent_printf (char*,...) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_long (scalar_t__,int) ; 

__attribute__((used)) static
void
test_IP_MIB_STATS(
    TDIEntityID Id,
    ULONG EntityType)
{
    IPSNMPInfo IpSnmpInfo;
    TCP_REQUEST_QUERY_INFORMATION_EX Request;
    ULONG BufferSize = 0;
    BOOL Result;

    /* Not valid for other entity types */
    if (EntityType != CL_NL_IP)
        return;

    ZeroMemory(&IpSnmpInfo, sizeof(IpSnmpInfo));

    ZeroMemory(&Request, sizeof(Request));
    Request.ID.toi_entity = Id;
    Request.ID.toi_class = INFO_CLASS_PROTOCOL;
    Request.ID.toi_type = INFO_TYPE_PROVIDER;
    Request.ID.toi_id = IP_MIB_STATS_ID;

    Result = DeviceIoControl(
        TcpFileHandle,
        IOCTL_TCP_QUERY_INFORMATION_EX,
        &Request,
        sizeof(Request),
        &IpSnmpInfo,
        sizeof(IpSnmpInfo),
        &BufferSize,
        NULL);
    ok(Result, "DeviceIoControl failed.\n");

    /* Dump it */
    indent_printf("IP_MIB Statistics:\n");
    IndentationLevel++;
    indent_printf("ipsi_forwarding:      %lu\n", IpSnmpInfo.ipsi_forwarding);
    indent_printf("ipsi_defaultttl:      %lu\n", IpSnmpInfo.ipsi_defaultttl);
    indent_printf("ipsi_inreceives:      %lu\n", IpSnmpInfo.ipsi_inreceives);
    indent_printf("ipsi_inhdrerrors:     %lu\n", IpSnmpInfo.ipsi_inhdrerrors);
    indent_printf("ipsi_inaddrerrors:    %lu\n", IpSnmpInfo.ipsi_inaddrerrors);
    indent_printf("ipsi_forwdatagrams:   %lu\n", IpSnmpInfo.ipsi_forwdatagrams);
    indent_printf("ipsi_inunknownprotos: %lu\n", IpSnmpInfo.ipsi_inunknownprotos);
    indent_printf("ipsi_indiscards:      %lu\n", IpSnmpInfo.ipsi_indiscards);
    indent_printf("ipsi_indelivers:      %lu\n", IpSnmpInfo.ipsi_indelivers);
    indent_printf("ipsi_outrequests:     %lu\n", IpSnmpInfo.ipsi_outrequests);
    indent_printf("ipsi_routingdiscards: %lu\n", IpSnmpInfo.ipsi_routingdiscards);
    indent_printf("ipsi_outdiscards:     %lu\n", IpSnmpInfo.ipsi_outdiscards);
    indent_printf("ipsi_outnoroutes:     %lu\n", IpSnmpInfo.ipsi_outnoroutes);
    indent_printf("ipsi_reasmtimeout:    %lu\n", IpSnmpInfo.ipsi_reasmtimeout);
    indent_printf("ipsi_reasmreqds:      %lu\n", IpSnmpInfo.ipsi_reasmreqds);
    indent_printf("ipsi_reasmoks:        %lu\n", IpSnmpInfo.ipsi_reasmoks);
    indent_printf("ipsi_reasmfails:      %lu\n", IpSnmpInfo.ipsi_reasmfails);
    indent_printf("ipsi_fragoks:         %lu\n", IpSnmpInfo.ipsi_fragoks);
    indent_printf("ipsi_fragfails:       %lu\n", IpSnmpInfo.ipsi_fragfails);
    indent_printf("ipsi_fragcreates:     %lu\n", IpSnmpInfo.ipsi_fragcreates);
    indent_printf("ipsi_numif:           %lu\n", IpSnmpInfo.ipsi_numif);
    indent_printf("ipsi_numaddr:         %lu\n", IpSnmpInfo.ipsi_numaddr);
    indent_printf("ipsi_numroutes:       %lu\n", IpSnmpInfo.ipsi_numroutes);

    if (IpSnmpInfo.ipsi_numaddr != 0)
    {
        IPAddrEntry* AddrEntries;
        ULONG i;

        AddrEntries = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, IpSnmpInfo.ipsi_numaddr * sizeof(AddrEntries[0]));
        ok(AddrEntries != NULL, "\n");

        ZeroMemory(&Request, sizeof(Request));
        Request.ID.toi_entity = Id;
        Request.ID.toi_class = INFO_CLASS_PROTOCOL;
        Request.ID.toi_type = INFO_TYPE_PROVIDER;
        Request.ID.toi_id = IP_MIB_ADDRTABLE_ENTRY_ID;

        Result = DeviceIoControl(
            TcpFileHandle,
            IOCTL_TCP_QUERY_INFORMATION_EX,
            &Request,
            sizeof(Request),
            AddrEntries,
            IpSnmpInfo.ipsi_numaddr * sizeof(AddrEntries[0]),
            &BufferSize,
            NULL);
        ok(Result, "DeviceIoControl failed.\n");
        ok_long(BufferSize, IpSnmpInfo.ipsi_numaddr * sizeof(AddrEntries[0]));

        for(i = 0; i < IpSnmpInfo.ipsi_numaddr; i++)
        {
            CHAR AddressString[16];
            struct in_addr Addr;

            Addr.S_un.S_addr = AddrEntries[i].iae_addr;
            RtlIpv4AddressToStringA(&Addr, AddressString);

            indent_printf("Address %lu: %s\n", i, AddressString);

            IndentationLevel++;

            indent_printf("iae_addr:      %lx\n", AddrEntries[i].iae_addr);
            indent_printf("iae_index:     %lu\n", AddrEntries[i].iae_index);
            Addr.S_un.S_addr = AddrEntries[i].iae_mask;
            RtlIpv4AddressToStringA(&Addr, AddressString);
            indent_printf("iae_mask:      %lx (%s)\n", AddrEntries[i].iae_mask, AddressString);
            indent_printf("iae_bcastaddr: %lu\n", AddrEntries[i].iae_bcastaddr);
            indent_printf("iae_reasmsize: %lu\n", AddrEntries[i].iae_reasmsize);
            indent_printf("iae_context:   %u\n",  AddrEntries[i].iae_context);

            {
                IPInterfaceInfo* InterfaceInfo;

                /* Get the interface info */
                BufferSize = sizeof(IPInterfaceInfo) + MAX_PHYSADDR_SIZE;
                InterfaceInfo = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BufferSize);
                ok(InterfaceInfo != NULL, "\n");

                Request.ID.toi_id = IP_INTFC_INFO_ID;
                Request.Context[0] = AddrEntries[i].iae_addr;
                Result = DeviceIoControl(
                    TcpFileHandle,
                    IOCTL_TCP_QUERY_INFORMATION_EX,
                    &Request,
                    sizeof(Request),
                    InterfaceInfo,
                    BufferSize,
                    &BufferSize,
                    NULL);
                ok(Result, "DeviceIoControl failed.\n");

                indent_printf("Interface info:\n");
                IndentationLevel++;

                indent_printf("iii_flags:    %lu\n", InterfaceInfo->iii_flags);
                indent_printf("iii_mtu  :    %lu\n", InterfaceInfo->iii_mtu);
                indent_printf("iii_speed:    %lu\n", InterfaceInfo->iii_speed);
                indent_printf("iii_physaddr: %s\n",  dbg_print_physaddr(InterfaceInfo->iii_addr, InterfaceInfo->iii_addrlength));

                IndentationLevel--;
            }

            IndentationLevel--;
        }

        HeapFree(GetProcessHeap(), 0, AddrEntries);
    }

    /* See for the routes */
    if (IpSnmpInfo.ipsi_numroutes)
    {
        IPRouteEntry* RouteEntries;
        ULONG i;

        RouteEntries = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, IpSnmpInfo.ipsi_numroutes * sizeof(RouteEntries[0]));
        ok(RouteEntries != NULL, "\n");

        ZeroMemory(&Request, sizeof(Request));
        Request.ID.toi_entity = Id;
        Request.ID.toi_class = INFO_CLASS_PROTOCOL;
        Request.ID.toi_type = INFO_TYPE_PROVIDER;
        Request.ID.toi_id = IP_MIB_ARPTABLE_ENTRY_ID;

        Result = DeviceIoControl(
            TcpFileHandle,
            IOCTL_TCP_QUERY_INFORMATION_EX,
            &Request,
            sizeof(Request),
            RouteEntries,
            IpSnmpInfo.ipsi_numroutes * sizeof(RouteEntries[0]),
            &BufferSize,
            NULL);
        ok(Result, "DeviceIoControl failed.\n");
        ok_long(BufferSize, IpSnmpInfo.ipsi_numroutes * sizeof(RouteEntries[0]));

        for (i = 0; i < IpSnmpInfo.ipsi_numroutes; i++)
        {
            CHAR AddressString[16];
            struct in_addr Addr;

            Addr.S_un.S_addr = RouteEntries[i].ire_dest;
            RtlIpv4AddressToStringA(&Addr, AddressString);

            indent_printf("Route %lu:\n", i);

            IndentationLevel++;

            indent_printf("ire_dest:    %s (%lx)\n", AddressString, RouteEntries[i].ire_dest);
            indent_printf("ire_index:   %lu\n", RouteEntries[i].ire_index);
            indent_printf("ire_metric1: %#lx\n", RouteEntries[i].ire_metric1);
            indent_printf("ire_metric2: %#lx\n", RouteEntries[i].ire_metric2);
            indent_printf("ire_metric3: %#lx\n", RouteEntries[i].ire_metric3);
            indent_printf("ire_metric4: %#lx\n", RouteEntries[i].ire_metric4);
            Addr.S_un.S_addr = RouteEntries[i].ire_nexthop;
            RtlIpv4AddressToStringA(&Addr, AddressString);
            indent_printf("ire_nexthop: %s (%lx)\n", AddressString, RouteEntries[i].ire_nexthop);
            indent_printf("ire_type:    %lu\n", RouteEntries[i].ire_type);
            indent_printf("ire_proto:   %lu\n", RouteEntries[i].ire_proto);
            indent_printf("ire_age:     %lu\n", RouteEntries[i].ire_age);
            Addr.S_un.S_addr = RouteEntries[i].ire_mask;
            RtlIpv4AddressToStringA(&Addr, AddressString);
            indent_printf("ire_mask:    %s (%lx)\n", AddressString, RouteEntries[i].ire_mask);
            indent_printf("ire_metric5: %lx\n", RouteEntries[i].ire_metric5);
            indent_printf("ire_context: %lx\n", RouteEntries[i].ire_context);

            IndentationLevel--;
        }
    }

    IndentationLevel--;
}