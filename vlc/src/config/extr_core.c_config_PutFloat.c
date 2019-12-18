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
struct TYPE_8__ {float f; } ;
struct TYPE_7__ {float f; } ;
struct TYPE_6__ {float f; } ;
struct TYPE_9__ {TYPE_3__ value; TYPE_2__ max; TYPE_1__ min; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_4__ module_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  IsConfigFloatType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__* config_FindConfig (char const*) ; 
 int config_dirty ; 
 int /*<<< orphan*/  config_lock ; 
 int /*<<< orphan*/  vlc_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_rwlock_wrlock (int /*<<< orphan*/ *) ; 

void config_PutFloat(const char *psz_name, float f_value)
{
    module_config_t *p_config = config_FindConfig( psz_name );

    /* sanity checks */
    assert(p_config != NULL);
    assert(IsConfigFloatType(p_config->i_type));

    /* if f_min == f_max == 0, then do not use them */
    if ((p_config->min.f == 0.f) && (p_config->max.f == 0.f))
        ;
    else if (f_value < p_config->min.f)
        f_value = p_config->min.f;
    else if (f_value > p_config->max.f)
        f_value = p_config->max.f;

    vlc_rwlock_wrlock (&config_lock);
    p_config->value.f = f_value;
    config_dirty = true;
    vlc_rwlock_unlock (&config_lock);
}