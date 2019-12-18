#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ vout_window_t ;
typedef  int /*<<< orphan*/  vout_window_cfg_t ;
struct TYPE_6__ {int (* enable ) (TYPE_2__*,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vout_window_SetInhibition (TYPE_2__*,int) ; 

int vout_window_Enable(vout_window_t *window,
                       const vout_window_cfg_t *restrict cfg)
{
    if (window->ops->enable != NULL) {
        int err = window->ops->enable(window, cfg);
        if (err)
            return err;
    }

    vout_window_SetInhibition(window, true);
    return VLC_SUCCESS;
}