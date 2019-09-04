#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  tei_instance; int /*<<< orphan*/  tei_entity; } ;
struct TYPE_9__ {int /*<<< orphan*/  if_index; } ;
struct TYPE_10__ {TYPE_1__ ent; } ;
struct TYPE_12__ {TYPE_2__ if_info; TYPE_6__ entity_id; } ;
struct TYPE_11__ {int numAllocated; int numIndexes; int /*<<< orphan*/ * indexes; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_3__ InterfaceIndexTable ;
typedef  TYPE_4__ IFInfo ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_READ_DATA ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getInterfaceInfoSet (int /*<<< orphan*/ ,TYPE_4__**,int*) ; 
 int /*<<< orphan*/  isLoopback (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  openTcpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdiFreeThingSet (TYPE_4__*) ; 

InterfaceIndexTable *getInterfaceIndexTableInt( BOOL nonLoopbackOnly ) {
  DWORD numInterfaces, curInterface = 0;
  int i;
  IFInfo *ifInfo;
  InterfaceIndexTable *ret = 0;
  HANDLE tcpFile;
  NTSTATUS status = openTcpFile( &tcpFile, FILE_READ_DATA );

  if( NT_SUCCESS(status) ) {
      status = getInterfaceInfoSet( tcpFile, &ifInfo, &numInterfaces );

      TRACE("InterfaceInfoSet: %08x, %04x:%08x\n",
             status,
             ifInfo->entity_id.tei_entity,
             ifInfo->entity_id.tei_instance);

      if( NT_SUCCESS(status) ) {
          ret = (InterfaceIndexTable *)
              calloc(1,
                     sizeof(InterfaceIndexTable) +
                     (numInterfaces - 1) * sizeof(DWORD));

          if (ret) {
              ret->numAllocated = numInterfaces;
              TRACE("NumInterfaces = %d\n", numInterfaces);

              for( i = 0; i < numInterfaces; i++ ) {
                  TRACE("Examining interface %d\n", i);
                  if( !nonLoopbackOnly ||
                      !isLoopback( tcpFile, &ifInfo[i].entity_id ) ) {
                      TRACE("Interface %d matches (%d)\n", i, curInterface);
                      ret->indexes[curInterface++] =
                          ifInfo[i].if_info.ent.if_index;
                  }
              }

              ret->numIndexes = curInterface;
          }

          tdiFreeThingSet( ifInfo );
      }
      closeTcpFile( tcpFile );
  }

  return ret;
}