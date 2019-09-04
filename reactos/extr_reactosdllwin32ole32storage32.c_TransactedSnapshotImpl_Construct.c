#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_13__ {int /*<<< orphan*/  lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int ref; int /*<<< orphan*/  storageDirEntry; int /*<<< orphan*/  openFlags; int /*<<< orphan*/  storageHead; int /*<<< orphan*/  strmHead; int /*<<< orphan*/ * baseVtbl; TYPE_2__ IPropertySetStorage_iface; TYPE_1__ IStorage_iface; } ;
struct TYPE_16__ {int entries_size; TYPE_4__ base; TYPE_6__* transactedParent; void* entries; scalar_t__ firstFreeEntry; int /*<<< orphan*/  scratch; int /*<<< orphan*/  lastTransactionSig; } ;
typedef  TYPE_5__ TransactedSnapshotImpl ;
typedef  int /*<<< orphan*/  TransactedDirEntry ;
struct TYPE_14__ {int /*<<< orphan*/  lpVtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/  storageDirEntry; TYPE_4__* transactedChild; int /*<<< orphan*/  openFlags; TYPE_3__ IPropertySetStorage_iface; } ;
typedef  TYPE_6__ StorageBaseImpl ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_DELETEONRELEASE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StgCreateDocfile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  StorageBaseImpl_GetTransactionSig (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactedSnapshotImpl_BaseVtbl ; 
 int /*<<< orphan*/  TransactedSnapshotImpl_CreateStubEntry (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactedSnapshotImpl_Vtbl ; 
 int /*<<< orphan*/  impl_from_IStorage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT TransactedSnapshotImpl_Construct(StorageBaseImpl *parentStorage,
  TransactedSnapshotImpl** result)
{
  HRESULT hr;

  *result = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(TransactedSnapshotImpl));
  if (*result)
  {
    IStorage *scratch;

    (*result)->base.IStorage_iface.lpVtbl = &TransactedSnapshotImpl_Vtbl;

    /* This is OK because the property set storage functions use the IStorage functions. */
    (*result)->base.IPropertySetStorage_iface.lpVtbl = parentStorage->IPropertySetStorage_iface.lpVtbl;
    (*result)->base.baseVtbl = &TransactedSnapshotImpl_BaseVtbl;

    list_init(&(*result)->base.strmHead);

    list_init(&(*result)->base.storageHead);

    (*result)->base.ref = 1;

    (*result)->base.openFlags = parentStorage->openFlags;

    /* This cannot fail, except with E_NOTIMPL in which case we don't care */
    StorageBaseImpl_GetTransactionSig(parentStorage, &(*result)->lastTransactionSig, FALSE);

    /* Create a new temporary storage to act as the scratch file. */
    hr = StgCreateDocfile(NULL, STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_DELETEONRELEASE,
        0, &scratch);
    (*result)->scratch = impl_from_IStorage(scratch);

    if (SUCCEEDED(hr))
    {
        ULONG num_entries = 20;

        (*result)->entries = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(TransactedDirEntry) * num_entries);
        (*result)->entries_size = num_entries;
        (*result)->firstFreeEntry = 0;

        if ((*result)->entries)
        {
            /* parentStorage already has 1 reference, which we take over here. */
            (*result)->transactedParent = parentStorage;

            parentStorage->transactedChild = &(*result)->base;

            (*result)->base.storageDirEntry = TransactedSnapshotImpl_CreateStubEntry(*result, parentStorage->storageDirEntry);
        }
        else
        {
            IStorage_Release(scratch);

            hr = E_OUTOFMEMORY;
        }
    }

    if (FAILED(hr)) HeapFree(GetProcessHeap(), 0, *result);

    return hr;
  }
  else
    return E_OUTOFMEMORY;
}