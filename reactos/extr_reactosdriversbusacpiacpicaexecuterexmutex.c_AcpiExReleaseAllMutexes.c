#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ ThreadId; int /*<<< orphan*/ * OwnerThread; scalar_t__ AcquisitionDepth; TYPE_5__* Next; int /*<<< orphan*/ * Prev; int /*<<< orphan*/  OriginalSyncLevel; int /*<<< orphan*/  OsMutex; int /*<<< orphan*/  SyncLevel; TYPE_2__* Node; } ;
struct TYPE_12__ {TYPE_3__ Mutex; } ;
struct TYPE_11__ {int /*<<< orphan*/  CurrentSyncLevel; TYPE_5__* AcquiredMutexList; } ;
struct TYPE_8__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_9__ {TYPE_1__ Name; } ;
typedef  TYPE_4__ ACPI_THREAD_STATE ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvReleaseGlobalLock () ; 
 TYPE_5__* AcpiGbl_GlobalLockMutex ; 
 int /*<<< orphan*/  AcpiOsReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseAllMutexes ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiExReleaseAllMutexes (
    ACPI_THREAD_STATE       *Thread)
{
    ACPI_OPERAND_OBJECT     *Next = Thread->AcquiredMutexList;
    ACPI_OPERAND_OBJECT     *ObjDesc;


    ACPI_FUNCTION_TRACE (ExReleaseAllMutexes);


    /* Traverse the list of owned mutexes, releasing each one */

    while (Next)
    {
        ObjDesc = Next;
        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "Mutex [%4.4s] force-release, SyncLevel %u Depth %u\n",
            ObjDesc->Mutex.Node->Name.Ascii, ObjDesc->Mutex.SyncLevel,
            ObjDesc->Mutex.AcquisitionDepth));

        /* Release the mutex, special case for Global Lock */

        if (ObjDesc == AcpiGbl_GlobalLockMutex)
        {
            /* Ignore errors */

            (void) AcpiEvReleaseGlobalLock ();
        }
        else
        {
            AcpiOsReleaseMutex (ObjDesc->Mutex.OsMutex);
        }

        /* Update Thread SyncLevel (Last mutex is the important one) */

        Thread->CurrentSyncLevel = ObjDesc->Mutex.OriginalSyncLevel;

        /* Mark mutex unowned */

        Next = ObjDesc->Mutex.Next;

        ObjDesc->Mutex.Prev = NULL;
        ObjDesc->Mutex.Next = NULL;
        ObjDesc->Mutex.AcquisitionDepth = 0;
        ObjDesc->Mutex.OwnerThread = NULL;
        ObjDesc->Mutex.ThreadId = 0;
    }

    return_VOID;
}