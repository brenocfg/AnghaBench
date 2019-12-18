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
struct TYPE_4__ {char* psz; } ;
struct TYPE_5__ {TYPE_1__ value; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_2__ module_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  IsConfigStringType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* config_FindConfig (char const*) ; 
 int config_dirty ; 
 int /*<<< orphan*/  config_lock ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  vlc_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_rwlock_wrlock (int /*<<< orphan*/ *) ; 

void config_PutPsz(const char *psz_name, const char *psz_value)
{
    module_config_t *p_config = config_FindConfig( psz_name );


    /* sanity checks */
    assert(p_config != NULL);
    assert(IsConfigStringType(p_config->i_type));

    char *str, *oldstr;
    if ((psz_value != NULL) && *psz_value)
        str = strdup (psz_value);
    else
        str = NULL;

    vlc_rwlock_wrlock (&config_lock);
    oldstr = (char *)p_config->value.psz;
    p_config->value.psz = str;
    config_dirty = true;
    vlc_rwlock_unlock (&config_lock);

    free (oldstr);
}