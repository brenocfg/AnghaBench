#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_5__ {TYPE_2__* sys; } ;
struct TYPE_6__ {TYPE_3__* p_sys; TYPE_1__ owner; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_7__ {int /*<<< orphan*/ * staging_pic; } ;
typedef  TYPE_3__ filter_sys_t ;

/* Variables and functions */

__attribute__((used)) static picture_t *NewBuffer(filter_t *p_filter)
{
    filter_t *p_parent = p_filter->owner.sys;
    filter_sys_t *p_sys = p_parent->p_sys;
    return p_sys->staging_pic;
}