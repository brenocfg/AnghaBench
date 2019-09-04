#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {TYPE_6__* DebugInfo; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int numIfaces; int ref3; TYPE_9__ IDirectPlayLobby3_iface; int /*<<< orphan*/  msgs; TYPE_8__ lock; scalar_t__ ref3A; scalar_t__ ref2A; scalar_t__ ref2; scalar_t__ refA; scalar_t__ ref; scalar_t__ msgtid; TYPE_5__ IDirectPlayLobby3A_iface; TYPE_4__ IDirectPlayLobby2A_iface; TYPE_3__ IDirectPlayLobby2_iface; TYPE_2__ IDirectPlayLobbyA_iface; TYPE_1__ IDirectPlayLobby_iface; } ;
struct TYPE_17__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_7__ IDirectPlayLobbyImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DPQ_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_7__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirectPlayLobby_QueryInterface (TYPE_9__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IDirectPlayLobby_Release (TYPE_9__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_8__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpl2A_vt ; 
 int /*<<< orphan*/  dpl2_vt ; 
 int /*<<< orphan*/  dpl3A_vt ; 
 int /*<<< orphan*/  dpl3_vt ; 
 int /*<<< orphan*/  dplA_vt ; 
 int /*<<< orphan*/  dpl_vt ; 

HRESULT dplobby_create( REFIID riid, void **ppv )
{
    IDirectPlayLobbyImpl *obj;
    HRESULT hr;

    TRACE( "(%s, %p)\n", debugstr_guid( riid ), ppv );

    *ppv = NULL;
    obj = HeapAlloc( GetProcessHeap(), 0, sizeof( *obj ) );
    if ( !obj )
        return DPERR_OUTOFMEMORY;

    obj->IDirectPlayLobby_iface.lpVtbl = &dpl_vt;
    obj->IDirectPlayLobbyA_iface.lpVtbl = &dplA_vt;
    obj->IDirectPlayLobby2_iface.lpVtbl = &dpl2_vt;
    obj->IDirectPlayLobby2A_iface.lpVtbl = &dpl2A_vt;
    obj->IDirectPlayLobby3_iface.lpVtbl = &dpl3_vt;
    obj->IDirectPlayLobby3A_iface.lpVtbl = &dpl3A_vt;
    obj->numIfaces = 1;
    obj->msgtid = 0;
    obj->ref = 0;
    obj->refA = 0;
    obj->ref2 = 0;
    obj->ref2A = 0;
    obj->ref3 = 1;
    obj->ref3A = 0;

    InitializeCriticalSection( &obj->lock );
    obj->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": IDirectPlayLobbyImpl.lock");
    DPQ_INIT( obj->msgs );

    hr = IDirectPlayLobby_QueryInterface( &obj->IDirectPlayLobby3_iface, riid, ppv );
    IDirectPlayLobby_Release( &obj->IDirectPlayLobby3_iface );

    return hr;
}