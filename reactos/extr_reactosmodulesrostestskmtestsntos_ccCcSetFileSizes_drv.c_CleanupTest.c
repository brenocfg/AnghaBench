#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {int /*<<< orphan*/ * SectionObjectPointer; int /*<<< orphan*/ * FsContext; } ;
struct TYPE_7__ {int /*<<< orphan*/  Event; } ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  TYPE_1__ CACHE_UNINITIALIZE_EVENT ;

/* Variables and functions */
 scalar_t__ CcIsFileCached (TYPE_2__*) ; 
 int /*<<< orphan*/  CcUninitializeCacheMap (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  ObDereferenceObject (TYPE_2__*) ; 
 int /*<<< orphan*/  RTL_CONSTANT_LARGE_INTEGER (long long) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * TestDeviceObject ; 
 TYPE_2__* TestFileObject ; 
 int TestTestId ; 
 int /*<<< orphan*/  TestUncaching ; 
 int /*<<< orphan*/  ok_eq_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_eq_ulong (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
VOID
CleanupTest(
    ULONG TestId,
    PDEVICE_OBJECT DeviceObject)
{
    LARGE_INTEGER Zero = RTL_CONSTANT_LARGE_INTEGER(0LL);
    CACHE_UNINITIALIZE_EVENT CacheUninitEvent;

    ok_eq_pointer(TestDeviceObject, DeviceObject);
    ok_eq_ulong(TestTestId, TestId);

    if (!skip(TestFileObject != NULL, "No test FO\n"))
    {
        if (CcIsFileCached(TestFileObject))
        {
            TestUncaching = TRUE;
            KeInitializeEvent(&CacheUninitEvent.Event, NotificationEvent, FALSE);
            CcUninitializeCacheMap(TestFileObject, &Zero, &CacheUninitEvent);
            KeWaitForSingleObject(&CacheUninitEvent.Event, Executive, KernelMode, FALSE, NULL);
            TestUncaching = FALSE;
        }

        if (TestFileObject->FsContext != NULL)
        {
            ExFreePool(TestFileObject->FsContext);
            TestFileObject->FsContext = NULL;
            TestFileObject->SectionObjectPointer = NULL;
        }

        ObDereferenceObject(TestFileObject);
    }

    TestFileObject = NULL;
    TestDeviceObject = NULL;
    TestTestId = -1;
}