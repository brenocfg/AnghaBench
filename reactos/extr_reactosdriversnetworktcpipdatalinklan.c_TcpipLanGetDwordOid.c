#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {scalar_t__ Context; } ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/  PLAN_ADAPTER ;
typedef  TYPE_1__* PIP_INTERFACE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int NDIS_OID ;

/* Variables and functions */
 int /*<<< orphan*/  NDISCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NdisHardwareStatusReady ; 
 int /*<<< orphan*/  NdisMediaStateConnected ; 
 int /*<<< orphan*/  NdisRequestQueryInformation ; 
#define  OID_GEN_HARDWARE_STATUS 129 
#define  OID_GEN_MEDIA_CONNECT_STATUS 128 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS TcpipLanGetDwordOid
( PIP_INTERFACE Interface,
  NDIS_OID Oid,
  PULONG Result ) {
    /* Get maximum frame size */
    if( Interface->Context ) {
        return NDISCall((PLAN_ADAPTER)Interface->Context,
                        NdisRequestQueryInformation,
                        Oid,
                        Result,
                        sizeof(ULONG));
    } else switch( Oid ) { /* Loopback Case */
    case OID_GEN_HARDWARE_STATUS:
        *Result = NdisHardwareStatusReady;
        return STATUS_SUCCESS;
    case OID_GEN_MEDIA_CONNECT_STATUS:
        *Result = NdisMediaStateConnected;
        return STATUS_SUCCESS;
    default:
        return STATUS_INVALID_PARAMETER;
    }
}