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
struct TYPE_5__ {int /*<<< orphan*/  f_float; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  sigma; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 float vlc_to_vdp_sigma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SharpenCallback(vlc_object_t *obj, const char *varname,
                           vlc_value_t prev, vlc_value_t cur, void *data)
{
    filter_sys_t *sys = data;
    union { uint32_t u; float f; } u;

    u.f = vlc_to_vdp_sigma(cur.f_float);
    atomic_store(&sys->sigma, u.u);
    (void) obj; (void) varname; (void) prev;
    return VLC_SUCCESS;
}