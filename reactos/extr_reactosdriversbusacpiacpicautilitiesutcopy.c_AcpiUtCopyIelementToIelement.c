#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  size_t UINT32 ;
struct TYPE_19__ {size_t Index; TYPE_6__* ThisTargetObj; TYPE_2__* DestObject; } ;
struct TYPE_21__ {TYPE_5__ Pkg; } ;
struct TYPE_18__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  Type; } ;
struct TYPE_17__ {int /*<<< orphan*/  Count; } ;
struct TYPE_20__ {TYPE_4__ Common; TYPE_3__ Package; } ;
struct TYPE_15__ {int /*<<< orphan*/ * Elements; } ;
struct TYPE_16__ {TYPE_1__ Package; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_6__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_7__ ACPI_GENERIC_STATE ;

/* Variables and functions */
#define  ACPI_COPY_TYPE_PACKAGE 129 
#define  ACPI_COPY_TYPE_SIMPLE 128 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiUtCopySimpleObject (TYPE_6__*,TYPE_6__*) ; 
 TYPE_6__* AcpiUtCreateInternalObject (int /*<<< orphan*/ ) ; 
 TYPE_6__* AcpiUtCreatePackageObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_6__*) ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtCopyIelementToIelement (
    UINT8                   ObjectType,
    ACPI_OPERAND_OBJECT     *SourceObject,
    ACPI_GENERIC_STATE      *State,
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;
    UINT32                  ThisIndex;
    ACPI_OPERAND_OBJECT     **ThisTargetPtr;
    ACPI_OPERAND_OBJECT     *TargetObject;


    ACPI_FUNCTION_ENTRY ();


    ThisIndex = State->Pkg.Index;
    ThisTargetPtr = (ACPI_OPERAND_OBJECT **)
        &State->Pkg.DestObject->Package.Elements[ThisIndex];

    switch (ObjectType)
    {
    case ACPI_COPY_TYPE_SIMPLE:

        /* A null source object indicates a (legal) null package element */

        if (SourceObject)
        {
            /*
             * This is a simple object, just copy it
             */
            TargetObject = AcpiUtCreateInternalObject (
                SourceObject->Common.Type);
            if (!TargetObject)
            {
                return (AE_NO_MEMORY);
            }

            Status = AcpiUtCopySimpleObject (SourceObject, TargetObject);
            if (ACPI_FAILURE (Status))
            {
                goto ErrorExit;
            }

            *ThisTargetPtr = TargetObject;
        }
        else
        {
            /* Pass through a null element */

            *ThisTargetPtr = NULL;
        }
        break;

    case ACPI_COPY_TYPE_PACKAGE:
        /*
         * This object is a package - go down another nesting level
         * Create and build the package object
         */
        TargetObject = AcpiUtCreatePackageObject (
            SourceObject->Package.Count);
        if (!TargetObject)
        {
            return (AE_NO_MEMORY);
        }

        TargetObject->Common.Flags = SourceObject->Common.Flags;

        /* Pass the new package object back to the package walk routine */

        State->Pkg.ThisTargetObj = TargetObject;

        /* Store the object pointer in the parent package object */

        *ThisTargetPtr = TargetObject;
        break;

    default:

        return (AE_BAD_PARAMETER);
    }

    return (Status);

ErrorExit:
    AcpiUtRemoveReference (TargetObject);
    return (Status);
}