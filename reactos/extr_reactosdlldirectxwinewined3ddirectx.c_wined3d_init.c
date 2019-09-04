#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d {int ref; int flags; int adapter_count; int /*<<< orphan*/ * adapters; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int WINED3D_NO3D ; 
 int /*<<< orphan*/  WINED3D_OK ; 
 int /*<<< orphan*/  wined3d_adapter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wined3d_adapter_init_nogl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HRESULT wined3d_init(struct wined3d *wined3d, DWORD flags)
{
    BOOL ret;

    wined3d->ref = 1;
    wined3d->flags = flags;

    TRACE("Initializing adapters.\n");

    if (flags & WINED3D_NO3D)
        ret = wined3d_adapter_init_nogl(&wined3d->adapters[0], 0);
    else
        ret = wined3d_adapter_init(&wined3d->adapters[0], 0, flags);
    if (!ret)
    {
        WARN("Failed to initialize adapter.\n");
        return E_FAIL;
    }
    wined3d->adapter_count = 1;

    return WINED3D_OK;
}