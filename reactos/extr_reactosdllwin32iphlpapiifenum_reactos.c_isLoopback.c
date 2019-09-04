#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ if_type; } ;
struct TYPE_5__ {TYPE_1__ ent; } ;
typedef  int /*<<< orphan*/  TDIEntityID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ IFEntrySafelySized ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ IFENT_SOFTWARE_LOOPBACK ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdiGetMibForIfEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 

BOOL isLoopback( HANDLE tcpFile, TDIEntityID *loop_maybe ) {
    IFEntrySafelySized entryInfo;
    NTSTATUS status;

    status = tdiGetMibForIfEntity( tcpFile,
                                   loop_maybe,
                                   &entryInfo );

    return NT_SUCCESS(status) &&
           (entryInfo.ent.if_type == IFENT_SOFTWARE_LOOPBACK);
}