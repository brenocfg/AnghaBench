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
struct TYPE_4__ {int /*<<< orphan*/  i; } ;
struct TYPE_5__ {TYPE_1__ value; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_2__ module_config_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  IsConfigIntegerType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* config_FindConfig (char const*) ; 
 int /*<<< orphan*/  config_lock ; 
 int /*<<< orphan*/  vlc_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_rwlock_unlock (int /*<<< orphan*/ *) ; 

int64_t config_GetInt(const char *psz_name)
{
    module_config_t *p_config = config_FindConfig( psz_name );

    /* sanity checks */
    assert(p_config != NULL);
    assert(IsConfigIntegerType(p_config->i_type));

    int64_t val;

    vlc_rwlock_rdlock (&config_lock);
    val = p_config->value.i;
    vlc_rwlock_unlock (&config_lock);
    return val;
}