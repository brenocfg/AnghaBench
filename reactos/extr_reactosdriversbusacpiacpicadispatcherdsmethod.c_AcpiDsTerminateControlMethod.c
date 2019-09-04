#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_22__ {TYPE_4__ Name; } ;
struct TYPE_19__ {int InfoFlags; int ThreadCount; scalar_t__ Node; int /*<<< orphan*/  OwnerId; scalar_t__ SyncLevel; TYPE_3__* Mutex; } ;
struct TYPE_21__ {TYPE_5__ Method; } ;
struct TYPE_20__ {TYPE_8__* MethodNode; TYPE_1__* Thread; } ;
struct TYPE_16__ {scalar_t__ ThreadId; int /*<<< orphan*/  OsMutex; int /*<<< orphan*/  OriginalSyncLevel; int /*<<< orphan*/  AcquisitionDepth; } ;
struct TYPE_17__ {TYPE_2__ Mutex; } ;
struct TYPE_15__ {int /*<<< orphan*/  CurrentSyncLevel; } ;
typedef  TYPE_6__ ACPI_WALK_STATE ;
typedef  TYPE_7__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ACPI_INFO (char*) ; 
 int ACPI_METHOD_IGNORE_SYNC_LEVEL ; 
 int ACPI_METHOD_MODIFIED_NAMESPACE ; 
 int ACPI_METHOD_MODULE_LEVEL ; 
 int ACPI_METHOD_SERIALIZED ; 
 int ACPI_METHOD_SERIALIZED_PENDING ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiDsMethodDataDeleteAll (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiExEnterInterpreter () ; 
 int /*<<< orphan*/  AcpiExExitInterpreter () ; 
 int /*<<< orphan*/  AcpiExStopTraceMethod (int /*<<< orphan*/ *,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiNsDeleteNamespaceByOwner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiNsDeleteNamespaceSubtree (TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiOsReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtReleaseOwnerId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsTerminateControlMethod ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiDsTerminateControlMethod (
    ACPI_OPERAND_OBJECT     *MethodDesc,
    ACPI_WALK_STATE         *WalkState)
{

    ACPI_FUNCTION_TRACE_PTR (DsTerminateControlMethod, WalkState);


    /* MethodDesc is required, WalkState is optional */

    if (!MethodDesc)
    {
        return_VOID;
    }

    if (WalkState)
    {
        /* Delete all arguments and locals */

        AcpiDsMethodDataDeleteAll (WalkState);

        /*
         * Delete any namespace objects created anywhere within the
         * namespace by the execution of this method. Unless:
         * 1) This method is a module-level executable code method, in which
         *    case we want make the objects permanent.
         * 2) There are other threads executing the method, in which case we
         *    will wait until the last thread has completed.
         */
        if (!(MethodDesc->Method.InfoFlags & ACPI_METHOD_MODULE_LEVEL) &&
             (MethodDesc->Method.ThreadCount == 1))
        {
            /* Delete any direct children of (created by) this method */

            (void) AcpiExExitInterpreter ();
            AcpiNsDeleteNamespaceSubtree (WalkState->MethodNode);
            (void) AcpiExEnterInterpreter ();

            /*
             * Delete any objects that were created by this method
             * elsewhere in the namespace (if any were created).
             * Use of the ACPI_METHOD_MODIFIED_NAMESPACE optimizes the
             * deletion such that we don't have to perform an entire
             * namespace walk for every control method execution.
             */
            if (MethodDesc->Method.InfoFlags & ACPI_METHOD_MODIFIED_NAMESPACE)
            {
                (void) AcpiExExitInterpreter ();
                AcpiNsDeleteNamespaceByOwner (MethodDesc->Method.OwnerId);
                (void) AcpiExEnterInterpreter ();
                MethodDesc->Method.InfoFlags &=
                    ~ACPI_METHOD_MODIFIED_NAMESPACE;
            }
        }

        /*
         * If method is serialized, release the mutex and restore the
         * current sync level for this thread
         */
        if (MethodDesc->Method.Mutex)
        {
            /* Acquisition Depth handles recursive calls */

            MethodDesc->Method.Mutex->Mutex.AcquisitionDepth--;
            if (!MethodDesc->Method.Mutex->Mutex.AcquisitionDepth)
            {
                WalkState->Thread->CurrentSyncLevel =
                    MethodDesc->Method.Mutex->Mutex.OriginalSyncLevel;

                AcpiOsReleaseMutex (
                    MethodDesc->Method.Mutex->Mutex.OsMutex);
                MethodDesc->Method.Mutex->Mutex.ThreadId = 0;
            }
        }
    }

    /* Decrement the thread count on the method */

    if (MethodDesc->Method.ThreadCount)
    {
        MethodDesc->Method.ThreadCount--;
    }
    else
    {
        ACPI_ERROR ((AE_INFO,
            "Invalid zero thread count in method"));
    }

    /* Are there any other threads currently executing this method? */

    if (MethodDesc->Method.ThreadCount)
    {
        /*
         * Additional threads. Do not release the OwnerId in this case,
         * we immediately reuse it for the next thread executing this method
         */
        ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
            "*** Completed execution of one thread, %u threads remaining\n",
            MethodDesc->Method.ThreadCount));
    }
    else
    {
        /* This is the only executing thread for this method */

        /*
         * Support to dynamically change a method from NotSerialized to
         * Serialized if it appears that the method is incorrectly written and
         * does not support multiple thread execution. The best example of this
         * is if such a method creates namespace objects and blocks. A second
         * thread will fail with an AE_ALREADY_EXISTS exception.
         *
         * This code is here because we must wait until the last thread exits
         * before marking the method as serialized.
         */
        if (MethodDesc->Method.InfoFlags & ACPI_METHOD_SERIALIZED_PENDING)
        {
            if (WalkState)
            {
                ACPI_INFO ((
                    "Marking method %4.4s as Serialized "
                    "because of AE_ALREADY_EXISTS error",
                    WalkState->MethodNode->Name.Ascii));
            }

            /*
             * Method tried to create an object twice and was marked as
             * "pending serialized". The probable cause is that the method
             * cannot handle reentrancy.
             *
             * The method was created as NotSerialized, but it tried to create
             * a named object and then blocked, causing the second thread
             * entrance to begin and then fail. Workaround this problem by
             * marking the method permanently as Serialized when the last
             * thread exits here.
             */
            MethodDesc->Method.InfoFlags &=
                ~ACPI_METHOD_SERIALIZED_PENDING;

            MethodDesc->Method.InfoFlags |=
                (ACPI_METHOD_SERIALIZED | ACPI_METHOD_IGNORE_SYNC_LEVEL);
            MethodDesc->Method.SyncLevel = 0;
        }

        /* No more threads, we can free the OwnerId */

        if (!(MethodDesc->Method.InfoFlags & ACPI_METHOD_MODULE_LEVEL))
        {
            AcpiUtReleaseOwnerId (&MethodDesc->Method.OwnerId);
        }
    }

    AcpiExStopTraceMethod ((ACPI_NAMESPACE_NODE *) MethodDesc->Method.Node,
        MethodDesc, WalkState);

    return_VOID;
}