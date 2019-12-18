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
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int config_SaveConfigFile (int /*<<< orphan*/ *) ; 
 int config_dirty ; 
 int /*<<< orphan*/  config_lock ; 
 int /*<<< orphan*/  vlc_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_rwlock_unlock (int /*<<< orphan*/ *) ; 

int config_AutoSaveConfigFile( vlc_object_t *p_this )
{
    int ret = 0;

    assert( p_this );

    vlc_rwlock_rdlock (&config_lock);
    if (config_dirty)
    {
        /* Note: this will get the read lock recursively. Ok. */
        ret = config_SaveConfigFile (p_this);
        config_dirty = (ret != 0);
    }
    vlc_rwlock_unlock (&config_lock);

    return ret;
}