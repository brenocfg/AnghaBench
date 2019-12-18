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
struct TYPE_4__ {int /*<<< orphan*/  psz; } ;
struct TYPE_5__ {TYPE_1__ value; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_2__ module_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  IsConfigStringType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* config_FindConfig (char const*) ; 
 int /*<<< orphan*/  config_lock ; 
 char* strdupnull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_rwlock_unlock (int /*<<< orphan*/ *) ; 

char *config_GetPsz(const char *psz_name)
{
    module_config_t *p_config;

    p_config = config_FindConfig( psz_name );

    /* sanity checks */
    assert(p_config != NULL);
    assert(IsConfigStringType (p_config->i_type));

    /* return a copy of the string */
    vlc_rwlock_rdlock (&config_lock);
    char *psz_value = strdupnull (p_config->value.psz);
    vlc_rwlock_unlock (&config_lock);

    return psz_value;
}