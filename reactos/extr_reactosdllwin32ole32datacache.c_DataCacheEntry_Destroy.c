#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  running_object; } ;
struct TYPE_7__ {int /*<<< orphan*/  ptd; } ;
struct TYPE_8__ {scalar_t__ sink_id; int /*<<< orphan*/  stgmedium; TYPE_1__ fmtetc; int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ DataCacheEntry ;
typedef  TYPE_3__ DataCache ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IDataObject_DUnadvise (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseStgMedium (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DataCacheEntry_Destroy(DataCache *cache, DataCacheEntry *cache_entry)
{
    list_remove(&cache_entry->entry);
    CoTaskMemFree(cache_entry->fmtetc.ptd);
    ReleaseStgMedium(&cache_entry->stgmedium);
    if(cache_entry->sink_id)
        IDataObject_DUnadvise(cache->running_object, cache_entry->sink_id);

    HeapFree(GetProcessHeap(), 0, cache_entry);
}