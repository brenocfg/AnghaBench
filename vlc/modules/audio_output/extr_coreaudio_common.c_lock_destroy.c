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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct aout_sys_common {TYPE_1__ lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_unfair_lock_lock ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
lock_destroy(struct aout_sys_common *p_sys)
{
    if (unlikely(!os_unfair_lock_lock))
        vlc_mutex_destroy(&p_sys->lock.mutex);
}