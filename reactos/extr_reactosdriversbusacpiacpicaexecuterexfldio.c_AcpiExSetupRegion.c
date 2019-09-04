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
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_10__ {scalar_t__ SpaceId; scalar_t__ Length; int /*<<< orphan*/  Node; } ;
struct TYPE_9__ {scalar_t__ BaseByteOffset; scalar_t__ AccessByteWidth; int /*<<< orphan*/  Node; TYPE_4__* RegionObj; } ;
struct TYPE_8__ {scalar_t__ Type; int Flags; } ;
struct TYPE_11__ {TYPE_3__ Region; TYPE_2__ CommonField; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_GSBUS ; 
 scalar_t__ ACPI_ADR_SPACE_IPMI ; 
 scalar_t__ ACPI_ADR_SPACE_SMBUS ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ACPI_ROUND_UP (scalar_t__,scalar_t__) ; 
 scalar_t__ ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AE_AML_INVALID_SPACE_ID ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_AML_REGION_LIMIT ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiDsGetRegionArguments (TYPE_4__*) ; 
 scalar_t__ AcpiGbl_EnableInterpreterSlack ; 
 int /*<<< orphan*/  AcpiIsValidSpaceId (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_4__*) ; 
 int /*<<< orphan*/  ExSetupRegion ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiExSetupRegion (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT32                  FieldDatumByteOffset)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OPERAND_OBJECT     *RgnDesc;
    UINT8                   SpaceId;


    ACPI_FUNCTION_TRACE_U32 (ExSetupRegion, FieldDatumByteOffset);


    RgnDesc = ObjDesc->CommonField.RegionObj;

    /* We must have a valid region */

    if (RgnDesc->Common.Type != ACPI_TYPE_REGION)
    {
        ACPI_ERROR ((AE_INFO, "Needed Region, found type 0x%X (%s)",
            RgnDesc->Common.Type,
            AcpiUtGetObjectTypeName (RgnDesc)));

        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }

    SpaceId = RgnDesc->Region.SpaceId;

    /* Validate the Space ID */

    if (!AcpiIsValidSpaceId (SpaceId))
    {
        ACPI_ERROR ((AE_INFO,
            "Invalid/unknown Address Space ID: 0x%2.2X", SpaceId));
        return_ACPI_STATUS (AE_AML_INVALID_SPACE_ID);
    }

    /*
     * If the Region Address and Length have not been previously evaluated,
     * evaluate them now and save the results.
     */
    if (!(RgnDesc->Common.Flags & AOPOBJ_DATA_VALID))
    {
        Status = AcpiDsGetRegionArguments (RgnDesc);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    /*
     * Exit now for SMBus, GSBus or IPMI address space, it has a non-linear
     * address space and the request cannot be directly validated
     */
    if (SpaceId == ACPI_ADR_SPACE_SMBUS ||
        SpaceId == ACPI_ADR_SPACE_GSBUS ||
        SpaceId == ACPI_ADR_SPACE_IPMI)
    {
        /* SMBus or IPMI has a non-linear address space */

        return_ACPI_STATUS (AE_OK);
    }

#ifdef ACPI_UNDER_DEVELOPMENT
    /*
     * If the Field access is AnyAcc, we can now compute the optimal
     * access (because we know know the length of the parent region)
     */
    if (!(ObjDesc->Common.Flags & AOPOBJ_DATA_VALID))
    {
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }
#endif

    /*
     * Validate the request. The entire request from the byte offset for a
     * length of one field datum (access width) must fit within the region.
     * (Region length is specified in bytes)
     */
    if (RgnDesc->Region.Length <
        (ObjDesc->CommonField.BaseByteOffset + FieldDatumByteOffset +
        ObjDesc->CommonField.AccessByteWidth))
    {
        if (AcpiGbl_EnableInterpreterSlack)
        {
            /*
             * Slack mode only:  We will go ahead and allow access to this
             * field if it is within the region length rounded up to the next
             * access width boundary. ACPI_SIZE cast for 64-bit compile.
             */
            if (ACPI_ROUND_UP (RgnDesc->Region.Length,
                    ObjDesc->CommonField.AccessByteWidth) >=
                ((ACPI_SIZE) ObjDesc->CommonField.BaseByteOffset +
                    ObjDesc->CommonField.AccessByteWidth +
                    FieldDatumByteOffset))
            {
                return_ACPI_STATUS (AE_OK);
            }
        }

        if (RgnDesc->Region.Length < ObjDesc->CommonField.AccessByteWidth)
        {
            /*
             * This is the case where the AccessType (AccWord, etc.) is wider
             * than the region itself. For example, a region of length one
             * byte, and a field with Dword access specified.
             */
            ACPI_ERROR ((AE_INFO,
                "Field [%4.4s] access width (%u bytes) "
                "too large for region [%4.4s] (length %u)",
                AcpiUtGetNodeName (ObjDesc->CommonField.Node),
                ObjDesc->CommonField.AccessByteWidth,
                AcpiUtGetNodeName (RgnDesc->Region.Node),
                RgnDesc->Region.Length));
        }

        /*
         * Offset rounded up to next multiple of field width
         * exceeds region length, indicate an error
         */
        ACPI_ERROR ((AE_INFO,
            "Field [%4.4s] Base+Offset+Width %u+%u+%u "
            "is beyond end of region [%4.4s] (length %u)",
            AcpiUtGetNodeName (ObjDesc->CommonField.Node),
            ObjDesc->CommonField.BaseByteOffset,
            FieldDatumByteOffset, ObjDesc->CommonField.AccessByteWidth,
            AcpiUtGetNodeName (RgnDesc->Region.Node),
            RgnDesc->Region.Length));

        return_ACPI_STATUS (AE_AML_REGION_LIMIT);
    }

    return_ACPI_STATUS (AE_OK);
}