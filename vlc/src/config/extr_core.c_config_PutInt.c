#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ i; } ;
struct TYPE_6__ {scalar_t__ i; } ;
struct TYPE_8__ {scalar_t__ i; } ;
struct TYPE_9__ {TYPE_2__ value; TYPE_1__ max; TYPE_3__ min; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_4__ module_config_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  IsConfigIntegerType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__* config_FindConfig (char const*) ; 
 int config_dirty ; 
 int /*<<< orphan*/  config_lock ; 
 int /*<<< orphan*/  vlc_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_rwlock_wrlock (int /*<<< orphan*/ *) ; 

void config_PutInt(const char *psz_name, int64_t i_value )
{
    module_config_t *p_config = config_FindConfig( psz_name );

    /* sanity checks */
    assert(p_config != NULL);
    assert(IsConfigIntegerType(p_config->i_type));

    if (i_value < p_config->min.i)
        i_value = p_config->min.i;
    if (i_value > p_config->max.i)
        i_value = p_config->max.i;

    vlc_rwlock_wrlock (&config_lock);
    p_config->value.i = i_value;
    config_dirty = true;
    vlc_rwlock_unlock (&config_lock);
}