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
struct TYPE_3__ {int /*<<< orphan*/ * hxdll; int /*<<< orphan*/  hd3d; } ;
typedef  TYPE_1__ vout_display_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3D9_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Direct3D9Destroy(vout_display_sys_t *sys)
{
    D3D9_Destroy( &sys->hd3d );

    if (sys->hxdll)
    {
        FreeLibrary(sys->hxdll);
        sys->hxdll = NULL;
    }
}