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
typedef  int UINT8 ;
typedef  int UINT32 ;
typedef  scalar_t__ BOOLEAN ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  scalar_t__ ACPI_OBJECT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DB_LOAD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ACPI_SUCCESS (scalar_t__) ; 
 scalar_t__ ACPI_TYPE_LOCAL_BANK_FIELD ; 
 scalar_t__ ACPI_TYPE_LOCAL_INDEX_FIELD ; 
 scalar_t__ ACPI_TYPE_LOCAL_REGION_FIELD ; 
 int ACPI_UINT32_MAX ; 
 scalar_t__ AE_AML_BAD_NAME ; 
 scalar_t__ AE_CTRL_PENDING ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_OK ; 
#define  AML_DUAL_NAME_PREFIX 131 
#define  AML_MULTI_NAME_PREFIX 130 
#define  AML_PARENT_PREFIX 129 
#define  AML_ROOT_PREFIX 128 
 char* AcpiExAllocateNameString (int,int) ; 
 scalar_t__ AcpiExNameSegment (int**,char*) ; 
 int /*<<< orphan*/  ExGetNameString ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

ACPI_STATUS
AcpiExGetNameString (
    ACPI_OBJECT_TYPE        DataType,
    UINT8                   *InAmlAddress,
    char                    **OutNameString,
    UINT32                  *OutNameLength)
{
    ACPI_STATUS             Status = AE_OK;
    UINT8                   *AmlAddress = InAmlAddress;
    char                    *NameString = NULL;
    UINT32                  NumSegments;
    UINT32                  PrefixCount = 0;
    BOOLEAN                 HasPrefix = FALSE;


    ACPI_FUNCTION_TRACE_PTR (ExGetNameString, AmlAddress);


    if (ACPI_TYPE_LOCAL_REGION_FIELD == DataType   ||
        ACPI_TYPE_LOCAL_BANK_FIELD == DataType     ||
        ACPI_TYPE_LOCAL_INDEX_FIELD == DataType)
    {
        /* Disallow prefixes for types associated with FieldUnit names */

        NameString = AcpiExAllocateNameString (0, 1);
        if (!NameString)
        {
            Status = AE_NO_MEMORY;
        }
        else
        {
            Status = AcpiExNameSegment (&AmlAddress, NameString);
        }
    }
    else
    {
        /*
         * DataType is not a field name.
         * Examine first character of name for root or parent prefix operators
         */
        switch (*AmlAddress)
        {
        case AML_ROOT_PREFIX:

            ACPI_DEBUG_PRINT ((ACPI_DB_LOAD, "RootPrefix(\\) at %p\n",
                AmlAddress));

            /*
             * Remember that we have a RootPrefix --
             * see comment in AcpiExAllocateNameString()
             */
            AmlAddress++;
            PrefixCount = ACPI_UINT32_MAX;
            HasPrefix = TRUE;
            break;

        case AML_PARENT_PREFIX:

            /* Increment past possibly multiple parent prefixes */

            do
            {
                ACPI_DEBUG_PRINT ((ACPI_DB_LOAD, "ParentPrefix (^) at %p\n",
                    AmlAddress));

                AmlAddress++;
                PrefixCount++;

            } while (*AmlAddress == AML_PARENT_PREFIX);

            HasPrefix = TRUE;
            break;

        default:

            /* Not a prefix character */

            break;
        }

        /* Examine first character of name for name segment prefix operator */

        switch (*AmlAddress)
        {
        case AML_DUAL_NAME_PREFIX:

            ACPI_DEBUG_PRINT ((ACPI_DB_LOAD, "DualNamePrefix at %p\n",
                AmlAddress));

            AmlAddress++;
            NameString = AcpiExAllocateNameString (PrefixCount, 2);
            if (!NameString)
            {
                Status = AE_NO_MEMORY;
                break;
            }

            /* Indicate that we processed a prefix */

            HasPrefix = TRUE;

            Status = AcpiExNameSegment (&AmlAddress, NameString);
            if (ACPI_SUCCESS (Status))
            {
                Status = AcpiExNameSegment (&AmlAddress, NameString);
            }
            break;

        case AML_MULTI_NAME_PREFIX:

            ACPI_DEBUG_PRINT ((ACPI_DB_LOAD, "MultiNamePrefix at %p\n",
                AmlAddress));

            /* Fetch count of segments remaining in name path */

            AmlAddress++;
            NumSegments = *AmlAddress;

            NameString = AcpiExAllocateNameString (
                PrefixCount, NumSegments);
            if (!NameString)
            {
                Status = AE_NO_MEMORY;
                break;
            }

            /* Indicate that we processed a prefix */

            AmlAddress++;
            HasPrefix = TRUE;

            while (NumSegments &&
                    (Status = AcpiExNameSegment (&AmlAddress, NameString)) ==
                        AE_OK)
            {
                NumSegments--;
            }

            break;

        case 0:

            /* NullName valid as of 8-12-98 ASL/AML Grammar Update */

            if (PrefixCount == ACPI_UINT32_MAX)
            {
                ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
                    "NameSeg is \"\\\" followed by NULL\n"));
            }

            /* Consume the NULL byte */

            AmlAddress++;
            NameString = AcpiExAllocateNameString (PrefixCount, 0);
            if (!NameString)
            {
                Status = AE_NO_MEMORY;
                break;
            }

            break;

        default:

            /* Name segment string */

            NameString = AcpiExAllocateNameString (PrefixCount, 1);
            if (!NameString)
            {
                Status = AE_NO_MEMORY;
                break;
            }

            Status = AcpiExNameSegment (&AmlAddress, NameString);
            break;
        }
    }

    if (AE_CTRL_PENDING == Status && HasPrefix)
    {
        /* Ran out of segments after processing a prefix */

        ACPI_ERROR ((AE_INFO,
            "Malformed Name at %p", NameString));
        Status = AE_AML_BAD_NAME;
    }

    if (ACPI_FAILURE (Status))
    {
        if (NameString)
        {
            ACPI_FREE (NameString);
        }
        return_ACPI_STATUS (Status);
    }

    *OutNameString = NameString;
    *OutNameLength = (UINT32) (AmlAddress - InAmlAddress);

    return_ACPI_STATUS (Status);
}