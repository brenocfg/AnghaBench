#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {TYPE_7__* DebugInfo; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_20__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_22__ {int numIfaces; int ref4; TYPE_10__ IDirectPlay4_iface; TYPE_9__ lock; scalar_t__ ref4A; scalar_t__ ref3; scalar_t__ ref3A; scalar_t__ ref2; scalar_t__ ref2A; scalar_t__ ref; TYPE_6__ IDirectPlay4A_iface; TYPE_5__ IDirectPlay3_iface; TYPE_4__ IDirectPlay3A_iface; TYPE_3__ IDirectPlay2_iface; TYPE_2__ IDirectPlay2A_iface; TYPE_1__ IDirectPlay_iface; } ;
struct TYPE_21__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_8__ IDirectPlayImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPERR_NOMEMORY ; 
 int /*<<< orphan*/  DPERR_OUTOFMEMORY ; 
 scalar_t__ DP_CreateDirectPlay2 (TYPE_8__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_8__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirectPlayX_QueryInterface (TYPE_10__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IDirectPlayX_Release (TYPE_10__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_9__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dp2A_vt ; 
 int /*<<< orphan*/  dp2_vt ; 
 int /*<<< orphan*/  dp3A_vt ; 
 int /*<<< orphan*/  dp3_vt ; 
 int /*<<< orphan*/  dp4A_vt ; 
 int /*<<< orphan*/  dp4_vt ; 
 int /*<<< orphan*/  dp_vt ; 

HRESULT dplay_create( REFIID riid, void **ppv )
{
    IDirectPlayImpl *obj;
    HRESULT hr;

    TRACE( "(%s, %p)\n", debugstr_guid( riid ), ppv );

    *ppv = NULL;
    obj = HeapAlloc( GetProcessHeap(), 0, sizeof( *obj ) );
    if ( !obj )
        return DPERR_OUTOFMEMORY;

    obj->IDirectPlay_iface.lpVtbl = &dp_vt;
    obj->IDirectPlay2A_iface.lpVtbl = &dp2A_vt;
    obj->IDirectPlay2_iface.lpVtbl = &dp2_vt;
    obj->IDirectPlay3A_iface.lpVtbl = &dp3A_vt;
    obj->IDirectPlay3_iface.lpVtbl = &dp3_vt;
    obj->IDirectPlay4A_iface.lpVtbl = &dp4A_vt;
    obj->IDirectPlay4_iface.lpVtbl = &dp4_vt;
    obj->numIfaces = 1;
    obj->ref = 0;
    obj->ref2A = 0;
    obj->ref2 = 0;
    obj->ref3A = 0;
    obj->ref3 = 0;
    obj->ref4A = 0;
    obj->ref4 = 1;

    InitializeCriticalSection( &obj->lock );
    obj->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": IDirectPlayImpl.lock");

    if ( DP_CreateDirectPlay2( obj ) )
        hr = IDirectPlayX_QueryInterface( &obj->IDirectPlay4_iface, riid, ppv );
    else
        hr = DPERR_NOMEMORY;
    IDirectPlayX_Release( &obj->IDirectPlay4_iface );

    return hr;
}