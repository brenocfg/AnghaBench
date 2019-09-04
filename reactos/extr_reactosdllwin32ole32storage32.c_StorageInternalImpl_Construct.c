#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int openFlags; int ref; void* create; int /*<<< orphan*/  storageDirEntry; void* reverted; int /*<<< orphan*/ * baseVtbl; TYPE_2__ IPropertySetStorage_iface; TYPE_1__ IStorage_iface; int /*<<< orphan*/  storageHead; int /*<<< orphan*/  strmHead; } ;
struct TYPE_10__ {TYPE_3__ base; int /*<<< orphan*/ * parentStorage; } ;
typedef  TYPE_4__ StorageInternalImpl ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;
typedef  int /*<<< orphan*/  DirRef ;
typedef  int DWORD ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IPropertySetStorage_Vtbl ; 
 int STGM_CREATE ; 
 int /*<<< orphan*/  StorageInternalImpl_BaseVtbl ; 
 int /*<<< orphan*/  StorageInternalImpl_Vtbl ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static StorageInternalImpl* StorageInternalImpl_Construct(
  StorageBaseImpl* parentStorage,
  DWORD        openFlags,
  DirRef       storageDirEntry)
{
  StorageInternalImpl* newStorage;

  newStorage = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(StorageInternalImpl));

  if (newStorage!=0)
  {
    list_init(&newStorage->base.strmHead);

    list_init(&newStorage->base.storageHead);

    /*
     * Initialize the virtual function table.
     */
    newStorage->base.IStorage_iface.lpVtbl = &StorageInternalImpl_Vtbl;
    newStorage->base.IPropertySetStorage_iface.lpVtbl = &IPropertySetStorage_Vtbl;
    newStorage->base.baseVtbl = &StorageInternalImpl_BaseVtbl;
    newStorage->base.openFlags = (openFlags & ~STGM_CREATE);

    newStorage->base.reverted = FALSE;

    newStorage->base.ref = 1;

    newStorage->parentStorage = parentStorage;

    /*
     * Keep a reference to the directory entry of this storage
     */
    newStorage->base.storageDirEntry = storageDirEntry;

    newStorage->base.create = FALSE;

    return newStorage;
  }

  return 0;
}