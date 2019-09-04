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
struct TYPE_5__ {int refs; TYPE_2__ IWineMsiRemoteDatabase_iface; scalar_t__ database; } ;
typedef  TYPE_1__ msi_remote_database_impl ;
typedef  TYPE_2__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_1__* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_remote_database_vtbl ; 

HRESULT create_msi_remote_database( IUnknown *pOuter, LPVOID *ppObj )
{
    msi_remote_database_impl *This;

    This = msi_alloc( sizeof *This );
    if (!This)
        return E_OUTOFMEMORY;

    This->IWineMsiRemoteDatabase_iface.lpVtbl = &msi_remote_database_vtbl;
    This->database = 0;
    This->refs = 1;

    *ppObj = &This->IWineMsiRemoteDatabase_iface;

    return S_OK;
}