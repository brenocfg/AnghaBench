#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  p_surface_handle; int /*<<< orphan*/  (* pf_unlockAndPost ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ NativeSurface ;
typedef  int /*<<< orphan*/  ANativeWindow ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
NativeSurface_unlockAndPost(ANativeWindow *p_anw)
{
    NativeSurface *p_ns = (NativeSurface *)p_anw;

    p_ns->pf_unlockAndPost(p_ns->p_surface_handle);
}