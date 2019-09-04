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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  CurrentPage; scalar_t__ IOBase; } ;
typedef  TYPE_1__* PNIC_ADAPTER ;

/* Variables and functions */
 int CR_PAGE0 ; 
 int CR_PAGE1 ; 
 int CR_RD2 ; 
 int CR_STA ; 
 int /*<<< orphan*/  NdisRawReadPortUchar (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisRawWritePortUchar (scalar_t__,int) ; 
 scalar_t__ PG0_CR ; 
 scalar_t__ PG1_CURR ; 

__attribute__((used)) static VOID NICGetCurrentPage(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Retrieves the current page from the adapter
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 */
{
    UCHAR Current;

    /* Select page 1 */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STA | CR_RD2 | CR_PAGE1);

    /* Read current page */
    NdisRawReadPortUchar(Adapter->IOBase + PG1_CURR, &Current);

    /* Select page 0 */
    NdisRawWritePortUchar(Adapter->IOBase + PG0_CR, CR_STA | CR_RD2 | CR_PAGE0);

    Adapter->CurrentPage = Current;
}