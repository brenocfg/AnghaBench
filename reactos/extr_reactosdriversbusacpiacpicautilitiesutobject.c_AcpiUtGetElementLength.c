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
typedef  int UINT8 ;
struct TYPE_5__ {int /*<<< orphan*/ * ThisTargetObj; } ;
struct TYPE_7__ {TYPE_1__ Pkg; } ;
struct TYPE_6__ {int /*<<< orphan*/  NumPackages; int /*<<< orphan*/  Length; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_SIZE ;
typedef  TYPE_2__ ACPI_PKG_INFO ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  TYPE_3__ ACPI_GENERIC_STATE ;

/* Variables and functions */
#define  ACPI_COPY_TYPE_PACKAGE 129 
#define  ACPI_COPY_TYPE_SIMPLE 128 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiUtGetSimpleObjectSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtGetElementLength (
    UINT8                   ObjectType,
    ACPI_OPERAND_OBJECT     *SourceObject,
    ACPI_GENERIC_STATE      *State,
    void                    *Context)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_PKG_INFO           *Info = (ACPI_PKG_INFO *) Context;
    ACPI_SIZE               ObjectSpace;


    switch (ObjectType)
    {
    case ACPI_COPY_TYPE_SIMPLE:
        /*
         * Simple object - just get the size (Null object/entry is handled
         * here also) and sum it into the running package length
         */
        Status = AcpiUtGetSimpleObjectSize (SourceObject, &ObjectSpace);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        Info->Length += ObjectSpace;
        break;

    case ACPI_COPY_TYPE_PACKAGE:

        /* Package object - nothing much to do here, let the walk handle it */

        Info->NumPackages++;
        State->Pkg.ThisTargetObj = NULL;
        break;

    default:

        /* No other types allowed */

        return (AE_BAD_PARAMETER);
    }

    return (Status);
}