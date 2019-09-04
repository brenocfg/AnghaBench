#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {scalar_t__ QuadPart; } ;
struct TYPE_9__ {int ref; TYPE_3__ IStream_iface; TYPE_3__* base; TYPE_1__ pos; void* length; void* start; } ;
typedef  TYPE_2__ sub_stream_t ;
typedef  void* ULARGE_INTEGER ;
typedef  TYPE_3__ IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IStream_AddRef (TYPE_3__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  sub_stream_vtbl ; 

__attribute__((used)) static HRESULT create_sub_stream(IStream *stream, ULARGE_INTEGER start, ULARGE_INTEGER length, IStream **out)
{
    sub_stream_t *This;

    *out = NULL;
    This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if(!This) return E_OUTOFMEMORY;

    This->IStream_iface.lpVtbl = &sub_stream_vtbl;
    This->ref = 1;
    This->start = start;
    This->length = length;
    This->pos.QuadPart = 0;
    IStream_AddRef(stream);
    This->base = stream;

    *out = &This->IStream_iface;
    return S_OK;
}