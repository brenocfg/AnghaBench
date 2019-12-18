#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_vout; } ;
typedef  TYPE_1__ goom_thread_t ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  vout_FlushAll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Flush( filter_t *p_filter )
{
    goom_thread_t *p_thread = p_filter->p_sys;
    vout_FlushAll( p_thread->p_vout );
}