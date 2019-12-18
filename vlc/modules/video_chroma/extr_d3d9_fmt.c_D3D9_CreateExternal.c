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
struct TYPE_3__ {int use_ex; int /*<<< orphan*/ * hdll; int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ d3d9_handle_t ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_GetDirect3D (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int D3D9_CreateExternal(d3d9_handle_t *hd3d, IDirect3DDevice9 *d3d9dev)
{
    HRESULT hr = IDirect3DDevice9_GetDirect3D(d3d9dev, &hd3d->obj);
    if (unlikely(FAILED(hr)))
        return VLC_EGENERIC;
    hd3d->hdll = NULL;
    hd3d->use_ex = false; /* we don't care */
    return VLC_SUCCESS;
}