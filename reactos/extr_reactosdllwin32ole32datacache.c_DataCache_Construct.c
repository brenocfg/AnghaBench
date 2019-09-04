#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_20__ {int ref; int last_cache_id; int /*<<< orphan*/  clsid; int /*<<< orphan*/ * running_object; void* dirty; int /*<<< orphan*/  cache_list; int /*<<< orphan*/ * presentationStorage; void* clsid_static; scalar_t__ sinkInterface; scalar_t__ sinkAdviseFlag; scalar_t__ sinkAspects; TYPE_7__ IUnknown_inner; TYPE_7__* outer_unk; TYPE_6__ IAdviseSink_iface; TYPE_5__ IOleCacheControl_iface; TYPE_4__ IOleCache2_iface; TYPE_3__ IViewObject2_iface; TYPE_2__ IPersistStorage_iface; TYPE_1__ IDataObject_iface; } ;
typedef  int /*<<< orphan*/ * REFCLSID ;
typedef  TYPE_7__* LPUNKNOWN ;
typedef  TYPE_8__ DataCache ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_NULL ; 
 int /*<<< orphan*/  DataCache_IAdviseSink_VTable ; 
 int /*<<< orphan*/  DataCache_IDataObject_VTable ; 
 int /*<<< orphan*/  DataCache_IOleCache2_VTable ; 
 int /*<<< orphan*/  DataCache_IOleCacheControl_VTable ; 
 int /*<<< orphan*/  DataCache_IPersistStorage_VTable ; 
 int /*<<< orphan*/  DataCache_IViewObject2_VTable ; 
 int /*<<< orphan*/  DataCache_NDIUnknown_VTable ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_8__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  create_automatic_entry (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DataCache* DataCache_Construct(
  REFCLSID  clsid,
  LPUNKNOWN pUnkOuter)
{
  DataCache* newObject = 0;

  /*
   * Allocate space for the object.
   */
  newObject = HeapAlloc(GetProcessHeap(), 0, sizeof(DataCache));

  if (newObject==0)
    return newObject;

  /*
   * Initialize the virtual function table.
   */
  newObject->IDataObject_iface.lpVtbl = &DataCache_IDataObject_VTable;
  newObject->IUnknown_inner.lpVtbl = &DataCache_NDIUnknown_VTable;
  newObject->IPersistStorage_iface.lpVtbl = &DataCache_IPersistStorage_VTable;
  newObject->IViewObject2_iface.lpVtbl = &DataCache_IViewObject2_VTable;
  newObject->IOleCache2_iface.lpVtbl = &DataCache_IOleCache2_VTable;
  newObject->IOleCacheControl_iface.lpVtbl = &DataCache_IOleCacheControl_VTable;
  newObject->IAdviseSink_iface.lpVtbl = &DataCache_IAdviseSink_VTable;
  newObject->outer_unk = pUnkOuter ? pUnkOuter : &newObject->IUnknown_inner;
  newObject->ref = 1;

  /*
   * Initialize the other members of the structure.
   */
  newObject->sinkAspects = 0;
  newObject->sinkAdviseFlag = 0;
  newObject->sinkInterface = 0;
  newObject->clsid = CLSID_NULL;
  newObject->clsid_static = FALSE;
  newObject->presentationStorage = NULL;
  list_init(&newObject->cache_list);
  newObject->last_cache_id = 2;
  newObject->dirty = FALSE;
  newObject->running_object = NULL;

  create_automatic_entry( newObject, clsid );
  newObject->clsid = *clsid;

  return newObject;
}