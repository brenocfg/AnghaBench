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
typedef  int /*<<< orphan*/  TDIEntityID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_READ_DATA ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 scalar_t__ isInterface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isLoopback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openTcpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdiFreeThingSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdiGetEntityIDSet (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static DWORD getNumInterfacesInt(BOOL onlyNonLoopback)
{
    DWORD numEntities, numInterfaces = 0;
    TDIEntityID *entitySet;
    HANDLE tcpFile;
    NTSTATUS status;
    int i;

    status = openTcpFile( &tcpFile, FILE_READ_DATA );

    if( !NT_SUCCESS(status) ) {
        WARN("getNumInterfaces: failed %08x\n", status );
        return 0;
    }

    status = tdiGetEntityIDSet( tcpFile, &entitySet, &numEntities );

    if( !NT_SUCCESS(status) ) {
        WARN("getNumInterfaces: failed %08x\n", status );
        closeTcpFile( tcpFile );
        return 0;
    }

    for( i = 0; i < numEntities; i++ ) {
        if( isInterface( &entitySet[i] ) &&
            (!onlyNonLoopback ||
             (onlyNonLoopback && !isLoopback( tcpFile, &entitySet[i] ))) )
            numInterfaces++;
    }

    TRACE("getNumInterfaces: success: %d %d %08x\n",
           onlyNonLoopback, numInterfaces, status );

    closeTcpFile( tcpFile );

    tdiFreeThingSet( entitySet );

    return numInterfaces;
}