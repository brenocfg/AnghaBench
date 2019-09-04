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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PDWORD ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ENTITY_LIST_ID ; 
 int /*<<< orphan*/  GENERIC_ENTITY ; 
 int /*<<< orphan*/  INFO_CLASS_GENERIC ; 
 int /*<<< orphan*/  INFO_TYPE_PROVIDER ; 
 int /*<<< orphan*/  tdiGetSetOfThings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS tdiGetEntityIDSet( HANDLE tcpFile,
                            TDIEntityID **entitySet,
                            PDWORD numEntities ) {
    NTSTATUS status = tdiGetSetOfThings( tcpFile,
                                         INFO_CLASS_GENERIC,
                                         INFO_TYPE_PROVIDER,
                                         ENTITY_LIST_ID,
                                         GENERIC_ENTITY,
                                         0,
                                         0,
                                         sizeof(TDIEntityID),
                                         (PVOID *)entitySet,
                                         numEntities );

    return status;
}