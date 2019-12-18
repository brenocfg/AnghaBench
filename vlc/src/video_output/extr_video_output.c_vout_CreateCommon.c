#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ vout_thread_t ;
typedef  int /*<<< orphan*/  vout_thread_sys_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vout_CreateVars (TYPE_1__*) ; 

__attribute__((used)) static vout_thread_t *vout_CreateCommon(vlc_object_t *object)
{
    /* Allocate descriptor */
    vout_thread_t *vout = vlc_custom_create(object,
                                            sizeof(*vout) + sizeof(*vout->p),
                                            "video output");
    if (!vout)
        return NULL;

    vout_CreateVars(vout);

    vout_thread_sys_t *sys = (vout_thread_sys_t *)&vout[1];

    vout->p = sys;
    return vout;
}