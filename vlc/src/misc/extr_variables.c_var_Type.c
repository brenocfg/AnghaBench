#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  var_lock; } ;
typedef  TYPE_1__ vlc_object_internals_t ;
struct TYPE_6__ {int i_type; scalar_t__ choices_count; } ;
typedef  TYPE_2__ variable_t ;

/* Variables and functions */
 TYPE_2__* Lookup (int /*<<< orphan*/ *,char const*) ; 
 int VLC_VAR_HASCHOICE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 TYPE_1__* vlc_internals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int (var_Type)(vlc_object_t *p_this, const char *psz_name)
{
    variable_t *p_var;
    int i_type = 0;

    assert( p_this );

    vlc_object_internals_t *p_priv = vlc_internals( p_this );

    p_var = Lookup( p_this, psz_name );
    if( p_var != NULL )
    {
        i_type = p_var->i_type;
        if (p_var->choices_count > 0)
            i_type |= VLC_VAR_HASCHOICE;
    }
    vlc_mutex_unlock( &p_priv->var_lock );

    return i_type;
}