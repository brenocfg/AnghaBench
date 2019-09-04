#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int TcpOffset; int TcpSize; int /*<<< orphan*/  TOIID; } ;
struct TYPE_12__ {scalar_t__ tei_entity; int dwNumEntries; int /*<<< orphan*/  tei_instance; } ;
typedef  TYPE_1__ TDIEntityID ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_1__* PMIB_TCPTABLE ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  size_t CLASS_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  Add2Ptr (TYPE_1__*,int) ; 
 scalar_t__ CO_TL_ENTITY ; 
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  FILE_READ_DATA ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INFO_CLASS_PROTOCOL ; 
 int /*<<< orphan*/  INFO_TYPE_PROVIDER ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_9__* UdpTcpTableCall ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 int getNumTcpEntries () ; 
 scalar_t__ hasArp (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ openTcpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdiFreeThingSet (TYPE_1__*) ; 
 scalar_t__ tdiGetEntityIDSet (int /*<<< orphan*/ ,TYPE_1__**,int*) ; 
 scalar_t__ tdiGetSetOfThings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__**,int*) ; 

PVOID getTcpTable(CLASS_TABLE Class)
{
    DWORD numEntities, returnSize;
    TDIEntityID *entitySet;
    HANDLE tcpFile;
    int i, totalNumber, TmpIdx, CurrIdx = 0;
    NTSTATUS status;
    PMIB_TCPTABLE IpTcpTable = NULL;
    PVOID AdapterTcpTable = NULL;

    TRACE("called.\n");

    totalNumber = getNumTcpEntries();

    status = openTcpFile( &tcpFile, FILE_READ_DATA );
    if( !NT_SUCCESS(status) ) {
        ERR("openTcpFile returned 0x%08lx\n", status);
        return 0;
    }

    IpTcpTable = HeapAlloc
	( GetProcessHeap(), 0,
	  UdpTcpTableCall[Class].TcpOffset + (UdpTcpTableCall[Class].TcpSize * totalNumber) );
    if (!IpTcpTable) {
        closeTcpFile(tcpFile);
        return NULL;
    }

    status = tdiGetEntityIDSet( tcpFile, &entitySet, &numEntities );

    for( i = 0; i < numEntities; i++ ) {
        if( entitySet[i].tei_entity == CO_TL_ENTITY &&
	    hasArp( tcpFile, &entitySet[i] ) ) {

	    status = tdiGetSetOfThings( tcpFile,
					INFO_CLASS_PROTOCOL,
					INFO_TYPE_PROVIDER,
					UdpTcpTableCall[Class].TOIID,
					CO_TL_ENTITY,
					entitySet[i].tei_instance,
					0,
					UdpTcpTableCall[Class].TcpSize,
					&AdapterTcpTable,
					&returnSize );

            if( status == STATUS_SUCCESS ) {
                for( TmpIdx = 0; TmpIdx < returnSize; TmpIdx++, CurrIdx++ )
                    CopyMemory(Add2Ptr(IpTcpTable, UdpTcpTableCall[Class].TcpOffset + UdpTcpTableCall[Class].TcpSize * CurrIdx),
                               Add2Ptr(AdapterTcpTable, UdpTcpTableCall[Class].TcpSize * TmpIdx),
                               UdpTcpTableCall[Class].TcpSize);
                tdiFreeThingSet( AdapterTcpTable );
            }
        }
    }

    closeTcpFile( tcpFile );

    tdiFreeThingSet( entitySet );
    IpTcpTable->dwNumEntries = CurrIdx;

    return IpTcpTable;
}