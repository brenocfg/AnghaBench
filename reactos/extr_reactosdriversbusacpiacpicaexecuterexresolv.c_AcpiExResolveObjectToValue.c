#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_19__ {int Type; } ;
struct TYPE_18__ {TYPE_1__* Node; int /*<<< orphan*/  TargetType; TYPE_5__** Where; int /*<<< orphan*/  Value; int /*<<< orphan*/  Class; } ;
struct TYPE_21__ {TYPE_3__ Common; TYPE_2__ Reference; } ;
struct TYPE_20__ {int /*<<< orphan*/  Opcode; } ;
struct TYPE_17__ {TYPE_5__* Object; int /*<<< orphan*/  Type; } ;
typedef  TYPE_4__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
#define  ACPI_REFCLASS_ARG 141 
#define  ACPI_REFCLASS_DEBUG 140 
#define  ACPI_REFCLASS_INDEX 139 
#define  ACPI_REFCLASS_LOCAL 138 
#define  ACPI_REFCLASS_NAME 137 
#define  ACPI_REFCLASS_REFOF 136 
#define  ACPI_REFCLASS_TABLE 135 
#define  ACPI_TYPE_BUFFER 134 
#define  ACPI_TYPE_BUFFER_FIELD 133 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 132 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 131 
#define  ACPI_TYPE_LOCAL_REFERENCE 130 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 129 
#define  ACPI_TYPE_PACKAGE 128 
 int /*<<< orphan*/  ACPI_TYPE_THERMAL ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_UNINITIALIZED_ELEMENT ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AML_COPY_OBJECT_OP ; 
 int /*<<< orphan*/  AML_INT_METHODCALL_OP ; 
 int /*<<< orphan*/  AcpiDsGetBufferArguments (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiDsGetPackageArguments (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiDsMethodDataGetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__**) ; 
 int /*<<< orphan*/  AcpiExReadDataFromField (TYPE_4__*,TYPE_5__*,TYPE_5__**) ; 
 int /*<<< orphan*/  AcpiUtAddReference (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_5__*) ; 
 int /*<<< orphan*/  ExResolveObjectToValue ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiExResolveObjectToValue (
    ACPI_OPERAND_OBJECT     **StackPtr,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OPERAND_OBJECT     *StackDesc;
    ACPI_OPERAND_OBJECT     *ObjDesc = NULL;
    UINT8                   RefType;


    ACPI_FUNCTION_TRACE (ExResolveObjectToValue);


    StackDesc = *StackPtr;

    /* This is an object of type ACPI_OPERAND_OBJECT */

    switch (StackDesc->Common.Type)
    {
    case ACPI_TYPE_LOCAL_REFERENCE:

        RefType = StackDesc->Reference.Class;

        switch (RefType)
        {
        case ACPI_REFCLASS_LOCAL:
        case ACPI_REFCLASS_ARG:
            /*
             * Get the local from the method's state info
             * Note: this increments the local's object reference count
             */
            Status = AcpiDsMethodDataGetValue (RefType,
                StackDesc->Reference.Value, WalkState, &ObjDesc);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }

            ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "[Arg/Local %X] ValueObj is %p\n",
                StackDesc->Reference.Value, ObjDesc));

            /*
             * Now we can delete the original Reference Object and
             * replace it with the resolved value
             */
            AcpiUtRemoveReference (StackDesc);
            *StackPtr = ObjDesc;
            break;

        case ACPI_REFCLASS_INDEX:

            switch (StackDesc->Reference.TargetType)
            {
            case ACPI_TYPE_BUFFER_FIELD:

                /* Just return - do not dereference */
                break;

            case ACPI_TYPE_PACKAGE:

                /* If method call or CopyObject - do not dereference */

                if ((WalkState->Opcode == AML_INT_METHODCALL_OP) ||
                    (WalkState->Opcode == AML_COPY_OBJECT_OP))
                {
                    break;
                }

                /* Otherwise, dereference the PackageIndex to a package element */

                ObjDesc = *StackDesc->Reference.Where;
                if (ObjDesc)
                {
                    /*
                     * Valid object descriptor, copy pointer to return value
                     * (i.e., dereference the package index)
                     * Delete the ref object, increment the returned object
                     */
                    AcpiUtAddReference (ObjDesc);
                    *StackPtr = ObjDesc;
                }
                else
                {
                    /*
                     * A NULL object descriptor means an uninitialized element of
                     * the package, can't dereference it
                     */
                    ACPI_ERROR ((AE_INFO,
                        "Attempt to dereference an Index to "
                        "NULL package element Idx=%p",
                        StackDesc));
                    Status = AE_AML_UNINITIALIZED_ELEMENT;
                }
                break;

            default:

                /* Invalid reference object */

                ACPI_ERROR ((AE_INFO,
                    "Unknown TargetType 0x%X in Index/Reference object %p",
                    StackDesc->Reference.TargetType, StackDesc));
                Status = AE_AML_INTERNAL;
                break;
            }
            break;

        case ACPI_REFCLASS_REFOF:
        case ACPI_REFCLASS_DEBUG:
        case ACPI_REFCLASS_TABLE:

            /* Just leave the object as-is, do not dereference */

            break;

        case ACPI_REFCLASS_NAME:   /* Reference to a named object */

            /* Dereference the name */

            if ((StackDesc->Reference.Node->Type == ACPI_TYPE_DEVICE) ||
                (StackDesc->Reference.Node->Type == ACPI_TYPE_THERMAL))
            {
                /* These node types do not have 'real' subobjects */

                *StackPtr = (void *) StackDesc->Reference.Node;
            }
            else
            {
                /* Get the object pointed to by the namespace node */

                *StackPtr = (StackDesc->Reference.Node)->Object;
                AcpiUtAddReference (*StackPtr);
            }

            AcpiUtRemoveReference (StackDesc);
            break;

        default:

            ACPI_ERROR ((AE_INFO,
                "Unknown Reference type 0x%X in %p",
                RefType, StackDesc));
            Status = AE_AML_INTERNAL;
            break;
        }
        break;

    case ACPI_TYPE_BUFFER:

        Status = AcpiDsGetBufferArguments (StackDesc);
        break;

    case ACPI_TYPE_PACKAGE:

        Status = AcpiDsGetPackageArguments (StackDesc);
        break;

    case ACPI_TYPE_BUFFER_FIELD:
    case ACPI_TYPE_LOCAL_REGION_FIELD:
    case ACPI_TYPE_LOCAL_BANK_FIELD:
    case ACPI_TYPE_LOCAL_INDEX_FIELD:

        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "FieldRead SourceDesc=%p Type=%X\n",
            StackDesc, StackDesc->Common.Type));

        Status = AcpiExReadDataFromField (WalkState, StackDesc, &ObjDesc);

        /* Remove a reference to the original operand, then override */

        AcpiUtRemoveReference (*StackPtr);
        *StackPtr = (void *) ObjDesc;
        break;

    default:

        break;
    }

    return_ACPI_STATUS (Status);
}