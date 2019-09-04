#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; int num_of_elems; TYPE_2__ IEnumSTATDATA_iface; int /*<<< orphan*/ * holder; TYPE_1__* statdata; int /*<<< orphan*/  index; } ;
struct TYPE_9__ {scalar_t__ pAdvSink; } ;
typedef  TYPE_1__ STATDATA ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ IEnumSTATDATA ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ EnumSTATDATA ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnumSTATDATA_VTable ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  copy_statdata (TYPE_1__*,TYPE_1__*) ; 

HRESULT EnumSTATDATA_Construct(IUnknown *holder, ULONG index, DWORD array_len, STATDATA *data,
                               BOOL copy, IEnumSTATDATA **ppenum)
{
    EnumSTATDATA *This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    DWORD i, count;

    if (!This) return E_OUTOFMEMORY;

    This->IEnumSTATDATA_iface.lpVtbl = &EnumSTATDATA_VTable;
    This->ref = 1;
    This->index = index;

    if (copy)
    {
        This->statdata = HeapAlloc(GetProcessHeap(), 0, array_len * sizeof(*This->statdata));
        if(!This->statdata)
        {
            HeapFree(GetProcessHeap(), 0, This);
            return E_OUTOFMEMORY;
        }

        for(i = 0, count = 0; i < array_len; i++)
        {
            if(data[i].pAdvSink)
            {
                copy_statdata(This->statdata + count, data + i);
                count++;
            }
        }
    }
    else
    {
        This->statdata = data;
        count = array_len;
    }

    This->num_of_elems = count;
    This->holder = holder;
    if (holder) IUnknown_AddRef(holder);
    *ppenum = &This->IEnumSTATDATA_iface;
    return S_OK;
}