#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* p_priv; } ;
typedef  TYPE_3__ addons_manager_t ;
struct TYPE_5__ {int b_live; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitcond; } ;
struct TYPE_4__ {TYPE_2__ finder; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void finder_thread_interrupted( void* p_data )
{
    addons_manager_t *p_manager = p_data;
    vlc_mutex_lock( &p_manager->p_priv->finder.lock );
    p_manager->p_priv->finder.b_live = false;
    vlc_cond_signal( &p_manager->p_priv->finder.waitcond );
    vlc_mutex_unlock( &p_manager->p_priv->finder.lock );
}