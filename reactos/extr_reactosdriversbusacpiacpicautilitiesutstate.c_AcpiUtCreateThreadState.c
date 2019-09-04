#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ThreadId; } ;
struct TYPE_5__ {int /*<<< orphan*/  DescriptorType; } ;
struct TYPE_7__ {TYPE_2__ Thread; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_THREAD_STATE ;
typedef  scalar_t__ ACPI_THREAD_ID ;
typedef  TYPE_3__ ACPI_GENERIC_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DESC_TYPE_STATE_THREAD ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AcpiOsGetThreadId () ; 
 TYPE_3__* AcpiUtCreateGenericState () ; 

ACPI_THREAD_STATE *
AcpiUtCreateThreadState (
    void)
{
    ACPI_GENERIC_STATE      *State;


    ACPI_FUNCTION_ENTRY ();


    /* Create the generic state object */

    State = AcpiUtCreateGenericState ();
    if (!State)
    {
        return (NULL);
    }

    /* Init fields specific to the update struct */

    State->Common.DescriptorType = ACPI_DESC_TYPE_STATE_THREAD;
    State->Thread.ThreadId = AcpiOsGetThreadId ();

    /* Check for invalid thread ID - zero is very bad, it will break things */

    if (!State->Thread.ThreadId)
    {
        ACPI_ERROR ((AE_INFO, "Invalid zero ID from AcpiOsGetThreadId"));
        State->Thread.ThreadId = (ACPI_THREAD_ID) 1;
    }

    return ((ACPI_THREAD_STATE *) State);
}