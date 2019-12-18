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
struct TYPE_3__ {int /*<<< orphan*/ * hdll; int /*<<< orphan*/ * obj; } ;
typedef  TYPE_1__ d3d9_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3D9_Release (int /*<<< orphan*/ *) ; 

void D3D9_Destroy(d3d9_handle_t *hd3d)
{
    if (hd3d->obj)
    {
       IDirect3D9_Release(hd3d->obj);
       hd3d->obj = NULL;
    }
    if (hd3d->hdll)
    {
        FreeLibrary(hd3d->hdll);
        hd3d->hdll = NULL;
    }
}