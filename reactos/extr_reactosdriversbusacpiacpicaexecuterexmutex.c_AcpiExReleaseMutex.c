#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_15__ {scalar_t__ SyncLevel; int /*<<< orphan*/  AcquisitionDepth; int /*<<< orphan*/  Node; TYPE_6__* OwnerThread; } ;
struct TYPE_18__ {TYPE_4__ Mutex; } ;
struct TYPE_17__ {scalar_t__ ThreadId; scalar_t__ CurrentSyncLevel; TYPE_2__* AcquiredMutexList; } ;
struct TYPE_16__ {TYPE_3__* Thread; } ;
struct TYPE_14__ {scalar_t__ ThreadId; int /*<<< orphan*/  CurrentSyncLevel; } ;
struct TYPE_12__ {scalar_t__ OriginalSyncLevel; } ;
struct TYPE_13__ {TYPE_1__ Mutex; } ;
typedef  TYPE_5__ ACPI_WALK_STATE ;
typedef  TYPE_6__ ACPI_THREAD_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_7__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_MUTEX_NOT_ACQUIRED ; 
 int /*<<< orphan*/  AE_AML_MUTEX_ORDER ; 
 int /*<<< orphan*/  AE_AML_NOT_OWNER ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiExReleaseMutexObject (TYPE_7__*) ; 
 TYPE_7__* AcpiGbl_GlobalLockMutex ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseMutex ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExReleaseMutex (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_WALK_STATE         *WalkState)
{
    UINT8                   PreviousSyncLevel;
    ACPI_THREAD_STATE       *OwnerThread;
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (ExReleaseMutex);


    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    OwnerThread = ObjDesc->Mutex.OwnerThread;

    /* The mutex must have been previously acquired in order to release it */

    if (!OwnerThread)
    {
        ACPI_ERROR ((AE_INFO,
            "Cannot release Mutex [%4.4s], not acquired",
            AcpiUtGetNodeName (ObjDesc->Mutex.Node)));
        return_ACPI_STATUS (AE_AML_MUTEX_NOT_ACQUIRED);
    }

    /* Must have a valid thread ID */

    if (!WalkState->Thread)
    {
        ACPI_ERROR ((AE_INFO,
            "Cannot release Mutex [%4.4s], null thread info",
            AcpiUtGetNodeName (ObjDesc->Mutex.Node)));
        return_ACPI_STATUS (AE_AML_INTERNAL);
    }

    /*
     * The Mutex is owned, but this thread must be the owner.
     * Special case for Global Lock, any thread can release
     */
    if ((OwnerThread->ThreadId != WalkState->Thread->ThreadId) &&
        (ObjDesc != AcpiGbl_GlobalLockMutex))
    {
        ACPI_ERROR ((AE_INFO,
            "Thread %u cannot release Mutex [%4.4s] acquired by thread %u",
            (UINT32) WalkState->Thread->ThreadId,
            AcpiUtGetNodeName (ObjDesc->Mutex.Node),
            (UINT32) OwnerThread->ThreadId));
        return_ACPI_STATUS (AE_AML_NOT_OWNER);
    }

    /*
     * The sync level of the mutex must be equal to the current sync level. In
     * other words, the current level means that at least one mutex at that
     * level is currently being held. Attempting to release a mutex of a
     * different level can only mean that the mutex ordering rule is being
     * violated. This behavior is clarified in ACPI 4.0 specification.
     */
    if (ObjDesc->Mutex.SyncLevel != OwnerThread->CurrentSyncLevel)
    {
        ACPI_ERROR ((AE_INFO,
            "Cannot release Mutex [%4.4s], SyncLevel mismatch: "
            "mutex %u current %u",
            AcpiUtGetNodeName (ObjDesc->Mutex.Node),
            ObjDesc->Mutex.SyncLevel, WalkState->Thread->CurrentSyncLevel));
        return_ACPI_STATUS (AE_AML_MUTEX_ORDER);
    }

    /*
     * Get the previous SyncLevel from the head of the acquired mutex list.
     * This handles the case where several mutexes at the same level have been
     * acquired, but are not released in reverse order.
     */
    PreviousSyncLevel =
        OwnerThread->AcquiredMutexList->Mutex.OriginalSyncLevel;

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "Releasing: Object SyncLevel %u, Thread SyncLevel %u, "
        "Prev SyncLevel %u, Depth %u TID %p\n",
        ObjDesc->Mutex.SyncLevel, WalkState->Thread->CurrentSyncLevel,
        PreviousSyncLevel, ObjDesc->Mutex.AcquisitionDepth,
        WalkState->Thread));

    Status = AcpiExReleaseMutexObject (ObjDesc);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    if (ObjDesc->Mutex.AcquisitionDepth == 0)
    {
        /* Restore the previous SyncLevel */

        OwnerThread->CurrentSyncLevel = PreviousSyncLevel;
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "Released: Object SyncLevel %u, Thread SyncLevel, %u, "
        "Prev SyncLevel %u, Depth %u\n",
        ObjDesc->Mutex.SyncLevel, WalkState->Thread->CurrentSyncLevel,
        PreviousSyncLevel, ObjDesc->Mutex.AcquisitionDepth));

    return_ACPI_STATUS (Status);
}