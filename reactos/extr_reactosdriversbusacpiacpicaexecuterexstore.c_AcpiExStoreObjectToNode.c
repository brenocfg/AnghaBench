#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_27__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_31__ {int Type; TYPE_1__ Name; } ;
struct TYPE_28__ {int const Type; } ;
struct TYPE_30__ {TYPE_2__ Common; } ;
struct TYPE_29__ {scalar_t__ Opcode; int /*<<< orphan*/  ResultObj; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;
typedef  int ACPI_OBJECT_TYPE ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
#define  ACPI_TYPE_BUFFER 142 
#define  ACPI_TYPE_BUFFER_FIELD 141 
#define  ACPI_TYPE_DEVICE 140 
#define  ACPI_TYPE_EVENT 139 
#define  ACPI_TYPE_INTEGER 138 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 137 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 136 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 135 
#define  ACPI_TYPE_MUTEX 134 
#define  ACPI_TYPE_PACKAGE 133 
#define  ACPI_TYPE_POWER 132 
#define  ACPI_TYPE_PROCESSOR 131 
#define  ACPI_TYPE_REGION 130 
#define  ACPI_TYPE_STRING 129 
#define  ACPI_TYPE_THERMAL 128 
 int /*<<< orphan*/  AE_AML_TARGET_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AML_COPY_OBJECT_OP ; 
 scalar_t__ AML_STORE_OP ; 
 int /*<<< orphan*/  AcpiExResolveObject (TYPE_4__**,int,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiExStoreDirectToNode (TYPE_4__*,TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiExStoreObjectToObject (TYPE_4__*,TYPE_4__*,TYPE_4__**,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiExWriteDataToField (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiNsAttachObject (TYPE_5__*,TYPE_4__*,int const) ; 
 TYPE_4__* AcpiNsGetAttachedObject (TYPE_5__*) ; 
 int AcpiNsGetType (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (int) ; 
 int /*<<< orphan*/  ExStoreObjectToNode ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExStoreObjectToNode (
    ACPI_OPERAND_OBJECT     *SourceDesc,
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_WALK_STATE         *WalkState,
    UINT8                   ImplicitConversion)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OPERAND_OBJECT     *TargetDesc;
    ACPI_OPERAND_OBJECT     *NewDesc;
    ACPI_OBJECT_TYPE        TargetType;


    ACPI_FUNCTION_TRACE_PTR (ExStoreObjectToNode, SourceDesc);


    /* Get current type of the node, and object attached to Node */

    TargetType = AcpiNsGetType (Node);
    TargetDesc = AcpiNsGetAttachedObject (Node);

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Storing %p [%s] to node %p [%s]\n",
        SourceDesc, AcpiUtGetObjectTypeName (SourceDesc),
        Node, AcpiUtGetTypeName (TargetType)));

    /* Only limited target types possible for everything except CopyObject */

    if (WalkState->Opcode != AML_COPY_OBJECT_OP)
    {
        /*
         * Only CopyObject allows all object types to be overwritten. For
         * TargetRef(s), there are restrictions on the object types that
         * are allowed.
         *
         * Allowable operations/typing for Store:
         *
         * 1) Simple Store
         *      Integer     --> Integer (Named/Local/Arg)
         *      String      --> String  (Named/Local/Arg)
         *      Buffer      --> Buffer  (Named/Local/Arg)
         *      Package     --> Package (Named/Local/Arg)
         *
         * 2) Store with implicit conversion
         *      Integer     --> String or Buffer  (Named)
         *      String      --> Integer or Buffer (Named)
         *      Buffer      --> Integer or String (Named)
         */
        switch (TargetType)
        {
        case ACPI_TYPE_PACKAGE:
            /*
             * Here, can only store a package to an existing package.
             * Storing a package to a Local/Arg is OK, and handled
             * elsewhere.
             */
            if (WalkState->Opcode == AML_STORE_OP)
            {
                if (SourceDesc->Common.Type != ACPI_TYPE_PACKAGE)
                {
                    ACPI_ERROR ((AE_INFO,
                        "Cannot assign type [%s] to [Package] "
                        "(source must be type Pkg)",
                        AcpiUtGetObjectTypeName (SourceDesc)));

                    return_ACPI_STATUS (AE_AML_TARGET_TYPE);
                }
                break;
            }

        /* Fallthrough */

        case ACPI_TYPE_DEVICE:
        case ACPI_TYPE_EVENT:
        case ACPI_TYPE_MUTEX:
        case ACPI_TYPE_REGION:
        case ACPI_TYPE_POWER:
        case ACPI_TYPE_PROCESSOR:
        case ACPI_TYPE_THERMAL:

            ACPI_ERROR ((AE_INFO,
                "Target must be [Buffer/Integer/String/Reference]"
                ", found [%s] (%4.4s)",
                AcpiUtGetTypeName (Node->Type), Node->Name.Ascii));

            return_ACPI_STATUS (AE_AML_TARGET_TYPE);

        default:
            break;
        }
    }

    /*
     * Resolve the source object to an actual value
     * (If it is a reference object)
     */
    Status = AcpiExResolveObject (&SourceDesc, TargetType, WalkState);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Do the actual store operation */

    switch (TargetType)
    {
        /*
         * The simple data types all support implicit source operand
         * conversion before the store.
         */
    case ACPI_TYPE_INTEGER:
    case ACPI_TYPE_STRING:
    case ACPI_TYPE_BUFFER:

        if ((WalkState->Opcode == AML_COPY_OBJECT_OP) ||
            !ImplicitConversion)
        {
            /*
             * However, CopyObject and Stores to ArgX do not perform
             * an implicit conversion, as per the ACPI specification.
             * A direct store is performed instead.
             */
            Status = AcpiExStoreDirectToNode (SourceDesc, Node, WalkState);
            break;
        }

        /* Store with implicit source operand conversion support */

        Status = AcpiExStoreObjectToObject (SourceDesc, TargetDesc,
            &NewDesc, WalkState);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        if (NewDesc != TargetDesc)
        {
            /*
             * Store the new NewDesc as the new value of the Name, and set
             * the Name's type to that of the value being stored in it.
             * SourceDesc reference count is incremented by AttachObject.
             *
             * Note: This may change the type of the node if an explicit
             * store has been performed such that the node/object type
             * has been changed.
             */
            Status = AcpiNsAttachObject (
                Node, NewDesc, NewDesc->Common.Type);

            ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
                "Store type [%s] into [%s] via Convert/Attach\n",
                AcpiUtGetObjectTypeName (SourceDesc),
                AcpiUtGetObjectTypeName (NewDesc)));
        }
        break;

    case ACPI_TYPE_BUFFER_FIELD:
    case ACPI_TYPE_LOCAL_REGION_FIELD:
    case ACPI_TYPE_LOCAL_BANK_FIELD:
    case ACPI_TYPE_LOCAL_INDEX_FIELD:
        /*
         * For all fields, always write the source data to the target
         * field. Any required implicit source operand conversion is
         * performed in the function below as necessary. Note, field
         * objects must retain their original type permanently.
         */
        Status = AcpiExWriteDataToField (SourceDesc, TargetDesc,
            &WalkState->ResultObj);
        break;

    default:
        /*
         * CopyObject operator: No conversions for all other types.
         * Instead, directly store a copy of the source object.
         *
         * This is the ACPI spec-defined behavior for the CopyObject
         * operator. (Note, for this default case, all normal
         * Store/Target operations exited above with an error).
         */
        Status = AcpiExStoreDirectToNode (SourceDesc, Node, WalkState);
        break;
    }

    return_ACPI_STATUS (Status);
}