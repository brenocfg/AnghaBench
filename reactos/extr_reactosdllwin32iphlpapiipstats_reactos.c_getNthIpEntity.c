#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tei_instance; int /*<<< orphan*/  tei_entity; } ;
typedef  TYPE_1__ TDIEntityID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 scalar_t__ isIpEntity (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  tdiFreeThingSet (TYPE_1__*) ; 
 int /*<<< orphan*/  tdiGetEntityIDSet (int /*<<< orphan*/ ,TYPE_1__**,int*) ; 

NTSTATUS getNthIpEntity( HANDLE tcpFile, DWORD index, TDIEntityID *ent ) {
    DWORD numEntities = 0;
    DWORD numRoutes = 0;
    TDIEntityID *entitySet = 0;
    NTSTATUS status = tdiGetEntityIDSet( tcpFile, &entitySet, &numEntities );
    int i;

    if( !NT_SUCCESS(status) )
        return status;

    for( i = 0; i < numEntities; i++ ) {
        if( isIpEntity( tcpFile, &entitySet[i] ) ) {
            TRACE("Entity %d is an IP Entity\n", i);
            if( numRoutes == index ) break;
            else numRoutes++;
        }
    }

    if( numRoutes == index && i < numEntities ) {
        TRACE("Index %lu is entity #%d - %04x:%08x\n", index, i,
              entitySet[i].tei_entity, entitySet[i].tei_instance);
        memcpy( ent, &entitySet[i], sizeof(*ent) );
        tdiFreeThingSet( entitySet );
        return STATUS_SUCCESS;
    } else {
        tdiFreeThingSet( entitySet );
        return STATUS_UNSUCCESSFUL;
    }
}