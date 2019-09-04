#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct TYPE_40__ {int /*<<< orphan*/ * Node; TYPE_14__* Mutex; } ;
struct TYPE_39__ {int /*<<< orphan*/  OsMutex; } ;
struct TYPE_38__ {int /*<<< orphan*/ * OsSemaphore; } ;
struct TYPE_37__ {TYPE_14__* Handler; } ;
struct TYPE_36__ {int /*<<< orphan*/  GpeBlock; } ;
struct TYPE_35__ {void* Elements; int /*<<< orphan*/  Count; } ;
struct TYPE_34__ {void* Pointer; } ;
struct TYPE_33__ {int Type; int Flags; } ;
struct TYPE_32__ {void* Pointer; } ;
struct TYPE_31__ {int Flags; } ;
struct TYPE_29__ {void* InternalPccBuffer; } ;
struct TYPE_28__ {int /*<<< orphan*/  RegionContext; } ;
struct TYPE_27__ {int HandlerFlags; int /*<<< orphan*/  Context; int /*<<< orphan*/  (* Setup ) (TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_14__* RegionList; TYPE_14__* Next; } ;
struct TYPE_26__ {TYPE_14__* Next; TYPE_14__* Handler; TYPE_17__* Node; int /*<<< orphan*/  SpaceId; } ;
struct TYPE_30__ {TYPE_13__ Field; TYPE_12__ Extra; TYPE_11__ AddressSpace; TYPE_10__ Region; TYPE_9__ Method; TYPE_8__ Mutex; TYPE_7__ Event; TYPE_6__ CommonNotify; TYPE_5__ Device; TYPE_4__ Package; TYPE_3__ Buffer; TYPE_2__ Common; TYPE_1__ String; } ;
typedef  TYPE_14__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int ACPI_ADDR_HANDLER_DEFAULT_INSTALLED ; 
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (void*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_14__*) ; 
 int /*<<< orphan*/  ACPI_GET_FUNCTION_NAME ; 
 int /*<<< orphan*/  ACPI_REGION_DEACTIVATE ; 
#define  ACPI_TYPE_BUFFER 139 
#define  ACPI_TYPE_BUFFER_FIELD 138 
#define  ACPI_TYPE_DEVICE 137 
#define  ACPI_TYPE_EVENT 136 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 135 
#define  ACPI_TYPE_METHOD 134 
#define  ACPI_TYPE_MUTEX 133 
#define  ACPI_TYPE_PACKAGE 132 
#define  ACPI_TYPE_PROCESSOR 131 
#define  ACPI_TYPE_REGION 130 
#define  ACPI_TYPE_STRING 129 
#define  ACPI_TYPE_THERMAL 128 
 int /*<<< orphan*/  AE_INFO ; 
 int ANOBJ_TEMPORARY ; 
 int AOPOBJ_STATIC_POINTER ; 
 int /*<<< orphan*/  AcpiEvDeleteGpeBlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiExUnlinkMutex (TYPE_14__*) ; 
 TYPE_14__* AcpiGbl_GlobalLockMutex ; 
 int /*<<< orphan*/ * AcpiGbl_GlobalLockSemaphore ; 
 TYPE_14__* AcpiNsGetSecondaryObject (TYPE_14__*) ; 
 int /*<<< orphan*/  AcpiOsDeleteMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsDeleteSemaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtDeleteObjectDesc (TYPE_14__*) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_14__*) ; 
 int /*<<< orphan*/  AcpiUtRemoveAddressRange (int /*<<< orphan*/ ,TYPE_17__*) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_14__*) ; 
 int /*<<< orphan*/  UtDeleteInternalObj ; 
 int /*<<< orphan*/  return_VOID ; 
 int /*<<< orphan*/  stub1 (TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
AcpiUtDeleteInternalObj (
    ACPI_OPERAND_OBJECT     *Object)
{
    void                    *ObjPointer = NULL;
    ACPI_OPERAND_OBJECT     *HandlerDesc;
    ACPI_OPERAND_OBJECT     *SecondDesc;
    ACPI_OPERAND_OBJECT     *NextDesc;
    ACPI_OPERAND_OBJECT     *StartDesc;
    ACPI_OPERAND_OBJECT     **LastObjPtr;


    ACPI_FUNCTION_TRACE_PTR (UtDeleteInternalObj, Object);


    if (!Object)
    {
        return_VOID;
    }

    /*
     * Must delete or free any pointers within the object that are not
     * actual ACPI objects (for example, a raw buffer pointer).
     */
    switch (Object->Common.Type)
    {
    case ACPI_TYPE_STRING:

        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS, "**** String %p, ptr %p\n",
            Object, Object->String.Pointer));

        /* Free the actual string buffer */

        if (!(Object->Common.Flags & AOPOBJ_STATIC_POINTER))
        {
            /* But only if it is NOT a pointer into an ACPI table */

            ObjPointer = Object->String.Pointer;
        }
        break;

    case ACPI_TYPE_BUFFER:

        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS, "**** Buffer %p, ptr %p\n",
            Object, Object->Buffer.Pointer));

        /* Free the actual buffer */

        if (!(Object->Common.Flags & AOPOBJ_STATIC_POINTER))
        {
            /* But only if it is NOT a pointer into an ACPI table */

            ObjPointer = Object->Buffer.Pointer;
        }
        break;

    case ACPI_TYPE_PACKAGE:

        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS, " **** Package of count %X\n",
            Object->Package.Count));

        /*
         * Elements of the package are not handled here, they are deleted
         * separately
         */

        /* Free the (variable length) element pointer array */

        ObjPointer = Object->Package.Elements;
        break;

    /*
     * These objects have a possible list of notify handlers.
     * Device object also may have a GPE block.
     */
    case ACPI_TYPE_DEVICE:

        if (Object->Device.GpeBlock)
        {
            (void) AcpiEvDeleteGpeBlock (Object->Device.GpeBlock);
        }

        /*lint -fallthrough */

    case ACPI_TYPE_PROCESSOR:
    case ACPI_TYPE_THERMAL:

        /* Walk the address handler list for this object */

        HandlerDesc = Object->CommonNotify.Handler;
        while (HandlerDesc)
        {
            NextDesc = HandlerDesc->AddressSpace.Next;
            AcpiUtRemoveReference (HandlerDesc);
            HandlerDesc = NextDesc;
        }
        break;

    case ACPI_TYPE_MUTEX:

        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS,
            "***** Mutex %p, OS Mutex %p\n",
            Object, Object->Mutex.OsMutex));

        if (Object == AcpiGbl_GlobalLockMutex)
        {
            /* Global Lock has extra semaphore */

            (void) AcpiOsDeleteSemaphore (AcpiGbl_GlobalLockSemaphore);
            AcpiGbl_GlobalLockSemaphore = NULL;

            AcpiOsDeleteMutex (Object->Mutex.OsMutex);
            AcpiGbl_GlobalLockMutex = NULL;
        }
        else
        {
            AcpiExUnlinkMutex (Object);
            AcpiOsDeleteMutex (Object->Mutex.OsMutex);
        }
        break;

    case ACPI_TYPE_EVENT:

        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS,
            "***** Event %p, OS Semaphore %p\n",
            Object, Object->Event.OsSemaphore));

        (void) AcpiOsDeleteSemaphore (Object->Event.OsSemaphore);
        Object->Event.OsSemaphore = NULL;
        break;

    case ACPI_TYPE_METHOD:

        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS,
            "***** Method %p\n", Object));

        /* Delete the method mutex if it exists */

        if (Object->Method.Mutex)
        {
            AcpiOsDeleteMutex (Object->Method.Mutex->Mutex.OsMutex);
            AcpiUtDeleteObjectDesc (Object->Method.Mutex);
            Object->Method.Mutex = NULL;
        }

        if (Object->Method.Node)
        {
            Object->Method.Node = NULL;
        }
        break;

    case ACPI_TYPE_REGION:

        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS,
            "***** Region %p\n", Object));

        /*
         * Update AddressRange list. However, only permanent regions
         * are installed in this list. (Not created within a method)
         */
        if (!(Object->Region.Node->Flags & ANOBJ_TEMPORARY))
        {
            AcpiUtRemoveAddressRange (Object->Region.SpaceId,
                Object->Region.Node);
        }

        SecondDesc = AcpiNsGetSecondaryObject (Object);
        if (SecondDesc)
        {
            /*
             * Free the RegionContext if and only if the handler is one of the
             * default handlers -- and therefore, we created the context object
             * locally, it was not created by an external caller.
             */
            HandlerDesc = Object->Region.Handler;
            if (HandlerDesc)
            {
                NextDesc = HandlerDesc->AddressSpace.RegionList;
                StartDesc = NextDesc;
                LastObjPtr = &HandlerDesc->AddressSpace.RegionList;

                /* Remove the region object from the handler list */

                while (NextDesc)
                {
                    if (NextDesc == Object)
                    {
                        *LastObjPtr = NextDesc->Region.Next;
                        break;
                    }

                    /* Walk the linked list of handlers */

                    LastObjPtr = &NextDesc->Region.Next;
                    NextDesc = NextDesc->Region.Next;

                    /* Prevent infinite loop if list is corrupted */

                    if (NextDesc == StartDesc)
                    {
                        ACPI_ERROR ((AE_INFO,
                            "Circular region list in address handler object %p",
                            HandlerDesc));
                        return_VOID;
                    }
                }

                if (HandlerDesc->AddressSpace.HandlerFlags &
                    ACPI_ADDR_HANDLER_DEFAULT_INSTALLED)
                {
                    /* Deactivate region and free region context */

                    if (HandlerDesc->AddressSpace.Setup)
                    {
                        (void) HandlerDesc->AddressSpace.Setup (Object,
                            ACPI_REGION_DEACTIVATE,
                            HandlerDesc->AddressSpace.Context,
                            &SecondDesc->Extra.RegionContext);
                    }
                }

                AcpiUtRemoveReference (HandlerDesc);
            }

            /* Now we can free the Extra object */

            AcpiUtDeleteObjectDesc (SecondDesc);
        }
        if (Object->Field.InternalPccBuffer)
        {
            ACPI_FREE(Object->Field.InternalPccBuffer);
        }

        break;

    case ACPI_TYPE_BUFFER_FIELD:

        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS,
            "***** Buffer Field %p\n", Object));

        SecondDesc = AcpiNsGetSecondaryObject (Object);
        if (SecondDesc)
        {
            AcpiUtDeleteObjectDesc (SecondDesc);
        }
        break;

    case ACPI_TYPE_LOCAL_BANK_FIELD:

        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS,
            "***** Bank Field %p\n", Object));

        SecondDesc = AcpiNsGetSecondaryObject (Object);
        if (SecondDesc)
        {
            AcpiUtDeleteObjectDesc (SecondDesc);
        }
        break;

    default:

        break;
    }

    /* Free any allocated memory (pointer within the object) found above */

    if (ObjPointer)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS, "Deleting Object Subptr %p\n",
            ObjPointer));
        ACPI_FREE (ObjPointer);
    }

    /* Now the object can be safely deleted */

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_ALLOCATIONS, "%s: Deleting Object %p [%s]\n",
        ACPI_GET_FUNCTION_NAME, Object, AcpiUtGetObjectTypeName (Object)));

    AcpiUtDeleteObjectDesc (Object);
    return_VOID;
}