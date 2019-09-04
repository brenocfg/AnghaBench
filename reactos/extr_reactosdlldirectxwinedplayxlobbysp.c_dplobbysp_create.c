#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IDPLobbySP_iface; int /*<<< orphan*/ * dplay; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IDirectPlayImpl ;
typedef  TYPE_1__ IDPLobbySPImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DPERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDPLobbySP_QueryInterface (TYPE_2__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IDPLobbySP_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpLobbySPVT ; 

HRESULT dplobbysp_create( REFIID riid, void **ppv, IDirectPlayImpl *dp )
{
  IDPLobbySPImpl *obj;
  HRESULT hr;

  TRACE( "(%s, %p)\n", debugstr_guid( riid ), ppv );

  *ppv = NULL;
  obj = HeapAlloc( GetProcessHeap(), 0, sizeof( *obj ) );
  if ( !obj )
    return DPERR_OUTOFMEMORY;

  obj->IDPLobbySP_iface.lpVtbl = &dpLobbySPVT;
  obj->ref = 1;
  obj->dplay = dp;

  hr = IDPLobbySP_QueryInterface( &obj->IDPLobbySP_iface, riid, ppv );
  IDPLobbySP_Release( &obj->IDPLobbySP_iface );

  return hr;
}