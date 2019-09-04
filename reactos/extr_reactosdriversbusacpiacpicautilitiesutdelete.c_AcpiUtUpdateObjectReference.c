#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_32__ {TYPE_11__* Object; int /*<<< orphan*/  Class; } ;
struct TYPE_31__ {TYPE_11__* DataObj; TYPE_11__* IndexObj; } ;
struct TYPE_30__ {TYPE_11__* RegionObj; TYPE_11__* BankObj; } ;
struct TYPE_29__ {TYPE_11__* RegionObj; } ;
struct TYPE_28__ {TYPE_11__* BufferObj; } ;
struct TYPE_27__ {int Type; } ;
struct TYPE_26__ {size_t Count; TYPE_11__** Elements; } ;
struct TYPE_25__ {TYPE_11__** Next; } ;
struct TYPE_24__ {TYPE_11__** NotifyList; } ;
struct TYPE_21__ {TYPE_11__* Object; } ;
struct TYPE_23__ {TYPE_10__ Update; } ;
struct TYPE_22__ {TYPE_9__ Reference; TYPE_8__ IndexField; TYPE_7__ BankField; TYPE_6__ Field; TYPE_5__ BufferField; TYPE_4__ Common; TYPE_3__ Package; TYPE_2__ Notify; TYPE_1__ CommonNotify; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_11__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_12__ ACPI_GENERIC_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (TYPE_11__*) ; 
 size_t ACPI_NUM_NOTIFY_TYPES ; 
 int /*<<< orphan*/  ACPI_REFCLASS_INDEX ; 
 int /*<<< orphan*/  ACPI_REFCLASS_NAME ; 
#define  ACPI_TYPE_BUFFER 141 
#define  ACPI_TYPE_BUFFER_FIELD 140 
#define  ACPI_TYPE_DEVICE 139 
#define  ACPI_TYPE_INTEGER 138 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 137 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 136 
#define  ACPI_TYPE_LOCAL_REFERENCE 135 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 134 
#define  ACPI_TYPE_PACKAGE 133 
#define  ACPI_TYPE_POWER 132 
#define  ACPI_TYPE_PROCESSOR 131 
#define  ACPI_TYPE_REGION 130 
#define  ACPI_TYPE_STRING 129 
#define  ACPI_TYPE_THERMAL 128 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiUtCreateUpdateStateAndPush (TYPE_11__*,int /*<<< orphan*/ ,TYPE_12__**) ; 
 int /*<<< orphan*/  AcpiUtDeleteGenericState (TYPE_12__*) ; 
 TYPE_12__* AcpiUtPopGenericState (TYPE_12__**) ; 
 int /*<<< orphan*/  AcpiUtUpdateRefCount (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtUpdateObjectReference ; 

ACPI_STATUS
AcpiUtUpdateObjectReference (
    ACPI_OPERAND_OBJECT     *Object,
    UINT16                  Action)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_GENERIC_STATE      *StateList = NULL;
    ACPI_OPERAND_OBJECT     *NextObject = NULL;
    ACPI_OPERAND_OBJECT     *PrevObject;
    ACPI_GENERIC_STATE      *State;
    UINT32                  i;


    ACPI_FUNCTION_NAME (UtUpdateObjectReference);


    while (Object)
    {
        /* Make sure that this isn't a namespace handle */

        if (ACPI_GET_DESCRIPTOR_TYPE (Object) == ACPI_DESC_TYPE_NAMED)
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS,
                "Object %p is NS handle\n", Object));
            return (AE_OK);
        }

        /*
         * All sub-objects must have their reference count incremented
         * also. Different object types have different subobjects.
         */
        switch (Object->Common.Type)
        {
        case ACPI_TYPE_DEVICE:
        case ACPI_TYPE_PROCESSOR:
        case ACPI_TYPE_POWER:
        case ACPI_TYPE_THERMAL:
            /*
             * Update the notify objects for these types (if present)
             * Two lists, system and device notify handlers.
             */
            for (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++)
            {
                PrevObject = Object->CommonNotify.NotifyList[i];
                while (PrevObject)
                {
                    NextObject = PrevObject->Notify.Next[i];
                    AcpiUtUpdateRefCount (PrevObject, Action);
                    PrevObject = NextObject;
                }
            }
            break;

        case ACPI_TYPE_PACKAGE:
            /*
             * We must update all the sub-objects of the package,
             * each of whom may have their own sub-objects.
             */
            for (i = 0; i < Object->Package.Count; i++)
            {
                /*
                 * Null package elements are legal and can be simply
                 * ignored.
                 */
                NextObject = Object->Package.Elements[i];
                if (!NextObject)
                {
                    continue;
                }

                switch (NextObject->Common.Type)
                {
                case ACPI_TYPE_INTEGER:
                case ACPI_TYPE_STRING:
                case ACPI_TYPE_BUFFER:
                    /*
                     * For these very simple sub-objects, we can just
                     * update the reference count here and continue.
                     * Greatly increases performance of this operation.
                     */
                    AcpiUtUpdateRefCount (NextObject, Action);
                    break;

                default:
                    /*
                     * For complex sub-objects, push them onto the stack
                     * for later processing (this eliminates recursion.)
                     */
                    Status = AcpiUtCreateUpdateStateAndPush (
                        NextObject, Action, &StateList);
                    if (ACPI_FAILURE (Status))
                    {
                        goto ErrorExit;
                    }
                    break;
                }
            }
            NextObject = NULL;
            break;

        case ACPI_TYPE_BUFFER_FIELD:

            NextObject = Object->BufferField.BufferObj;
            break;

        case ACPI_TYPE_LOCAL_REGION_FIELD:

            NextObject = Object->Field.RegionObj;
            break;

        case ACPI_TYPE_LOCAL_BANK_FIELD:

            NextObject = Object->BankField.BankObj;
            Status = AcpiUtCreateUpdateStateAndPush (
                Object->BankField.RegionObj, Action, &StateList);
            if (ACPI_FAILURE (Status))
            {
                goto ErrorExit;
            }
            break;

        case ACPI_TYPE_LOCAL_INDEX_FIELD:

            NextObject = Object->IndexField.IndexObj;
            Status = AcpiUtCreateUpdateStateAndPush (
                Object->IndexField.DataObj, Action, &StateList);
            if (ACPI_FAILURE (Status))
            {
                goto ErrorExit;
            }
            break;

        case ACPI_TYPE_LOCAL_REFERENCE:
            /*
             * The target of an Index (a package, string, or buffer) or a named
             * reference must track changes to the ref count of the index or
             * target object.
             */
            if ((Object->Reference.Class == ACPI_REFCLASS_INDEX) ||
                (Object->Reference.Class== ACPI_REFCLASS_NAME))
            {
                NextObject = Object->Reference.Object;
            }
            break;

        case ACPI_TYPE_REGION:
        default:

            break; /* No subobjects for all other types */
        }

        /*
         * Now we can update the count in the main object. This can only
         * happen after we update the sub-objects in case this causes the
         * main object to be deleted.
         */
        AcpiUtUpdateRefCount (Object, Action);
        Object = NULL;

        /* Move on to the next object to be updated */

        if (NextObject)
        {
            Object = NextObject;
            NextObject = NULL;
        }
        else if (StateList)
        {
            State = AcpiUtPopGenericState (&StateList);
            Object = State->Update.Object;
            AcpiUtDeleteGenericState (State);
        }
    }

    return (AE_OK);


ErrorExit:

    ACPI_EXCEPTION ((AE_INFO, Status,
        "Could not update object reference count"));

    /* Free any stacked Update State objects */

    while (StateList)
    {
        State = AcpiUtPopGenericState (&StateList);
        AcpiUtDeleteGenericState (State);
    }

    return (Status);
}