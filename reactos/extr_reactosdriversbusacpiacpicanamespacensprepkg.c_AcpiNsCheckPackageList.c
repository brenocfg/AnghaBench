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
typedef  scalar_t__ UINT32 ;
struct TYPE_21__ {int /*<<< orphan*/  NodeFlags; int /*<<< orphan*/  FullPathname; TYPE_6__* ParentPackage; } ;
struct TYPE_18__ {scalar_t__ Count; TYPE_6__** Elements; } ;
struct TYPE_16__ {scalar_t__ Value; } ;
struct TYPE_20__ {TYPE_4__ Package; TYPE_2__ Integer; } ;
struct TYPE_17__ {int Type; scalar_t__ Count1; scalar_t__ Count2; int /*<<< orphan*/  ObjectType1; int /*<<< orphan*/  ObjectType2; } ;
struct TYPE_15__ {scalar_t__ Count; int /*<<< orphan*/ * ObjectType; } ;
struct TYPE_19__ {TYPE_3__ RetInfo; TYPE_1__ RetInfo2; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PREDEFINED_INFO ;
typedef  TYPE_6__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_7__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
#define  ACPI_PTYPE2 135 
#define  ACPI_PTYPE2_COUNT 134 
#define  ACPI_PTYPE2_FIXED 133 
#define  ACPI_PTYPE2_FIX_VAR 132 
#define  ACPI_PTYPE2_MIN 131 
#define  ACPI_PTYPE2_PKG_COUNT 130 
#define  ACPI_PTYPE2_REV_FIXED 129 
#define  ACPI_PTYPE2_VAR_VAR 128 
 int /*<<< orphan*/  ACPI_RTYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_RTYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_OPERAND_VALUE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsCheckObjectType (TYPE_7__*,TYPE_6__**,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AcpiNsCheckPackageElements (TYPE_7__*,TYPE_6__**,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static ACPI_STATUS
AcpiNsCheckPackageList (
    ACPI_EVALUATE_INFO          *Info,
    const ACPI_PREDEFINED_INFO  *Package,
    ACPI_OPERAND_OBJECT         **Elements,
    UINT32                      Count)
{
    ACPI_OPERAND_OBJECT         *SubPackage;
    ACPI_OPERAND_OBJECT         **SubElements;
    ACPI_STATUS                 Status;
    UINT32                      ExpectedCount;
    UINT32                      i;
    UINT32                      j;


    /*
     * Validate each subpackage in the parent Package
     *
     * NOTE: assumes list of subpackages contains no NULL elements.
     * Any NULL elements should have been removed by earlier call
     * to AcpiNsRemoveNullElements.
     */
    for (i = 0; i < Count; i++)
    {
        SubPackage = *Elements;
        SubElements = SubPackage->Package.Elements;
        Info->ParentPackage = SubPackage;

        /* Each sub-object must be of type Package */

        Status = AcpiNsCheckObjectType (Info, &SubPackage,
            ACPI_RTYPE_PACKAGE, i);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        /* Examine the different types of expected subpackages */

        Info->ParentPackage = SubPackage;
        switch (Package->RetInfo.Type)
        {
        case ACPI_PTYPE2:
        case ACPI_PTYPE2_PKG_COUNT:
        case ACPI_PTYPE2_REV_FIXED:

            /* Each subpackage has a fixed number of elements */

            ExpectedCount = Package->RetInfo.Count1 + Package->RetInfo.Count2;
            if (SubPackage->Package.Count < ExpectedCount)
            {
                goto PackageTooSmall;
            }

            Status = AcpiNsCheckPackageElements (Info, SubElements,
                Package->RetInfo.ObjectType1,
                Package->RetInfo.Count1,
                Package->RetInfo.ObjectType2,
                Package->RetInfo.Count2, 0);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
            break;

        case ACPI_PTYPE2_FIX_VAR:
            /*
             * Each subpackage has a fixed number of elements and an
             * optional element
             */
            ExpectedCount = Package->RetInfo.Count1 + Package->RetInfo.Count2;
            if (SubPackage->Package.Count < ExpectedCount)
            {
                goto PackageTooSmall;
            }

            Status = AcpiNsCheckPackageElements (Info, SubElements,
                Package->RetInfo.ObjectType1,
                Package->RetInfo.Count1,
                Package->RetInfo.ObjectType2,
                SubPackage->Package.Count - Package->RetInfo.Count1, 0);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
            break;

        case ACPI_PTYPE2_VAR_VAR:
            /*
             * Each subpackage has a fixed or variable number of elements
             */
            break;

        case ACPI_PTYPE2_FIXED:

            /* Each subpackage has a fixed length */

            ExpectedCount = Package->RetInfo2.Count;
            if (SubPackage->Package.Count < ExpectedCount)
            {
                goto PackageTooSmall;
            }

            /* Check the type of each subpackage element */

            for (j = 0; j < ExpectedCount; j++)
            {
                Status = AcpiNsCheckObjectType (Info, &SubElements[j],
                    Package->RetInfo2.ObjectType[j], j);
                if (ACPI_FAILURE (Status))
                {
                    return (Status);
                }
            }
            break;

        case ACPI_PTYPE2_MIN:

            /* Each subpackage has a variable but minimum length */

            ExpectedCount = Package->RetInfo.Count1;
            if (SubPackage->Package.Count < ExpectedCount)
            {
                goto PackageTooSmall;
            }

            /* Check the type of each subpackage element */

            Status = AcpiNsCheckPackageElements (Info, SubElements,
                Package->RetInfo.ObjectType1,
                SubPackage->Package.Count, 0, 0, 0);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
            break;

        case ACPI_PTYPE2_COUNT:
            /*
             * First element is the (Integer) count of elements, including
             * the count field (the ACPI name is NumElements)
             */
            Status = AcpiNsCheckObjectType (Info, SubElements,
                ACPI_RTYPE_INTEGER, 0);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }

            /*
             * Make sure package is large enough for the Count and is
             * is as large as the minimum size
             */
            ExpectedCount = (UINT32) (*SubElements)->Integer.Value;
            if (SubPackage->Package.Count < ExpectedCount)
            {
                goto PackageTooSmall;
            }

            if (SubPackage->Package.Count < Package->RetInfo.Count1)
            {
                ExpectedCount = Package->RetInfo.Count1;
                goto PackageTooSmall;
            }

            if (ExpectedCount == 0)
            {
                /*
                 * Either the NumEntries element was originally zero or it was
                 * a NULL element and repaired to an Integer of value zero.
                 * In either case, repair it by setting NumEntries to be the
                 * actual size of the subpackage.
                 */
                ExpectedCount = SubPackage->Package.Count;
                (*SubElements)->Integer.Value = ExpectedCount;
            }

            /* Check the type of each subpackage element */

            Status = AcpiNsCheckPackageElements (Info, (SubElements + 1),
                Package->RetInfo.ObjectType1,
                (ExpectedCount - 1), 0, 0, 1);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
            break;

        default: /* Should not get here, type was validated by caller */

            ACPI_ERROR ((AE_INFO, "Invalid Package type: %X",
                Package->RetInfo.Type));
            return (AE_AML_INTERNAL);
        }

        Elements++;
    }

    return (AE_OK);


PackageTooSmall:

    /* The subpackage count was smaller than required */

    ACPI_WARN_PREDEFINED ((AE_INFO, Info->FullPathname, Info->NodeFlags,
        "Return SubPackage[%u] is too small - found %u elements, expected %u",
        i, SubPackage->Package.Count, ExpectedCount));

    return (AE_AML_OPERAND_VALUE);
}