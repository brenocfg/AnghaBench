#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_6__ {scalar_t__ ReferenceCount; int /*<<< orphan*/  Type; } ;
struct TYPE_7__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_CPU_FLAGS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_GET_FUNCTION_NAME ; 
 scalar_t__ ACPI_MAX_REFERENCE_COUNT ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiGbl_ReferenceCountLock ; 
 int /*<<< orphan*/  AcpiOsAcquireLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsReleaseLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtDeleteInternalObj (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_2__*) ; 
#define  REF_DECREMENT 129 
#define  REF_INCREMENT 128 
 int /*<<< orphan*/  UtUpdateRefCount ; 

__attribute__((used)) static void
AcpiUtUpdateRefCount (
    ACPI_OPERAND_OBJECT     *Object,
    UINT32                  Action)
{
    UINT16                  OriginalCount;
    UINT16                  NewCount = 0;
    ACPI_CPU_FLAGS          LockFlags;
    char                    *Message;


    ACPI_FUNCTION_NAME (UtUpdateRefCount);


    if (!Object)
    {
        return;
    }

    /*
     * Always get the reference count lock. Note: Interpreter and/or
     * Namespace is not always locked when this function is called.
     */
    LockFlags = AcpiOsAcquireLock (AcpiGbl_ReferenceCountLock);
    OriginalCount = Object->Common.ReferenceCount;

    /* Perform the reference count action (increment, decrement) */

    switch (Action)
    {
    case REF_INCREMENT:

        NewCount = OriginalCount + 1;
        Object->Common.ReferenceCount = NewCount;
        AcpiOsReleaseLock (AcpiGbl_ReferenceCountLock, LockFlags);

        /* The current reference count should never be zero here */

        if (!OriginalCount)
        {
            ACPI_WARNING ((AE_INFO,
                "Obj %p, Reference Count was zero before increment\n",
                Object));
        }

        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS,
            "Obj %p Type %.2X [%s] Refs %.2X [Incremented]\n",
            Object, Object->Common.Type,
            AcpiUtGetObjectTypeName (Object), NewCount));
        Message = "Incremement";
        break;

    case REF_DECREMENT:

        /* The current reference count must be non-zero */

        if (OriginalCount)
        {
            NewCount = OriginalCount - 1;
            Object->Common.ReferenceCount = NewCount;
        }

        AcpiOsReleaseLock (AcpiGbl_ReferenceCountLock, LockFlags);

        if (!OriginalCount)
        {
            ACPI_WARNING ((AE_INFO,
                "Obj %p, Reference Count is already zero, cannot decrement\n",
                Object));
        }

        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_ALLOCATIONS,
            "%s: Obj %p Type %.2X Refs %.2X [Decremented]\n",
            ACPI_GET_FUNCTION_NAME, Object, Object->Common.Type, NewCount));

        /* Actually delete the object on a reference count of zero */

        if (NewCount == 0)
        {
            AcpiUtDeleteInternalObj (Object);
        }
        Message = "Decrement";
        break;

    default:

        AcpiOsReleaseLock (AcpiGbl_ReferenceCountLock, LockFlags);
        ACPI_ERROR ((AE_INFO, "Unknown Reference Count action (0x%X)",
            Action));
        return;
    }

    /*
     * Sanity check the reference count, for debug purposes only.
     * (A deleted object will have a huge reference count)
     */
    if (NewCount > ACPI_MAX_REFERENCE_COUNT)
    {
        ACPI_WARNING ((AE_INFO,
            "Large Reference Count (0x%X) in object %p, Type=0x%.2X Operation=%s",
            NewCount, Object, Object->Common.Type, Message));
    }
}