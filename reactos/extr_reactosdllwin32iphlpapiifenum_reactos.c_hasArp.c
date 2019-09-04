#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_8__ {int /*<<< orphan*/  tei_instance; int /*<<< orphan*/  tei_entity; } ;
struct TYPE_9__ {TYPE_1__ toi_entity; int /*<<< orphan*/  toi_id; int /*<<< orphan*/  toi_type; int /*<<< orphan*/  toi_class; } ;
struct TYPE_11__ {TYPE_2__ ID; } ;
struct TYPE_10__ {int /*<<< orphan*/  tei_instance; } ;
typedef  TYPE_3__ TDIEntityID ;
typedef  TYPE_4__ TCP_REQUEST_QUERY_INFORMATION_EX ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int AT_ARP ; 
 int /*<<< orphan*/  AT_ENTITY ; 
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int,int*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENTITY_TYPE_ID ; 
 int FALSE ; 
 int /*<<< orphan*/  INFO_CLASS_GENERIC ; 
 int /*<<< orphan*/  INFO_TYPE_PROVIDER ; 
 int /*<<< orphan*/  IOCTL_TCP_QUERY_INFORMATION_EX ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 TYPE_4__ TCP_REQUEST_QUERY_INFORMATION_INIT ; 

BOOL hasArp( HANDLE tcpFile, TDIEntityID *arp_maybe ) {
    TCP_REQUEST_QUERY_INFORMATION_EX req = TCP_REQUEST_QUERY_INFORMATION_INIT;
    NTSTATUS status = STATUS_SUCCESS;
    DWORD returnSize, type;

    req.ID.toi_class                = INFO_CLASS_GENERIC;
    req.ID.toi_type                 = INFO_TYPE_PROVIDER;
    req.ID.toi_id                   = ENTITY_TYPE_ID;
    req.ID.toi_entity.tei_entity    = AT_ENTITY;
    req.ID.toi_entity.tei_instance  = arp_maybe->tei_instance;

    status = DeviceIoControl( tcpFile,
                              IOCTL_TCP_QUERY_INFORMATION_EX,
                              &req,
                              sizeof(req),
                              &type,
                              sizeof(type),
                              &returnSize,
                              NULL );
    if( !NT_SUCCESS(status) ) return FALSE;

    return (type & AT_ARP);
}