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
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  int /*<<< orphan*/  D3DSURFACE_DESC ;
typedef  int /*<<< orphan*/  D3DLOCKED_RECT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DLOCK_READONLY ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DSurface9_GetDesc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DSurface9_LockRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool GetLock(filter_t *p_filter, IDirect3DSurface9 *d3d,
                    D3DLOCKED_RECT *p_lock, D3DSURFACE_DESC *p_desc)
{
    if (unlikely(FAILED( IDirect3DSurface9_GetDesc(d3d, p_desc))))
        return false;

    /* */
    if (FAILED(IDirect3DSurface9_LockRect(d3d, p_lock, NULL, D3DLOCK_READONLY))) {
        msg_Err(p_filter, "Failed to lock surface");
        return false;
    }

    return true;
}