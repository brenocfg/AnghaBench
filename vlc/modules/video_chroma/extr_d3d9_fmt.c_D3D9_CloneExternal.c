#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  use_ex; int /*<<< orphan*/ * hdll; int /*<<< orphan*/ * obj; } ;
typedef  TYPE_1__ d3d9_handle_t ;
typedef  int /*<<< orphan*/  IDirect3D9Ex ;
typedef  int /*<<< orphan*/  IDirect3D9 ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3D9Ex_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3D9_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3D9_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDirect3D9Ex ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 

void D3D9_CloneExternal(d3d9_handle_t *hd3d, IDirect3D9 *dev)
{
    hd3d->obj = dev;
    IDirect3D9_AddRef( hd3d->obj );
    hd3d->hdll = NULL;

    void *pv = NULL;
    hd3d->use_ex = SUCCEEDED(IDirect3D9_QueryInterface(dev, &IID_IDirect3D9Ex, &pv));
    if (hd3d->use_ex && pv)
        IDirect3D9Ex_Release((IDirect3D9Ex*) pv);
}