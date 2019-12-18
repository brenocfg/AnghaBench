#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {int /*<<< orphan*/  var_lock; } ;
typedef  TYPE_2__ vlc_object_internals_t ;
struct TYPE_11__ {int i_type; TYPE_1__* ops; int /*<<< orphan*/  val; } ;
typedef  TYPE_3__ variable_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* pf_free ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* pf_dup ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CheckValue (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* Lookup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  TriggerCallback (int /*<<< orphan*/ *,TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 int VLC_ENOVAR ; 
 int VLC_SUCCESS ; 
 int VLC_VAR_CLASS ; 
 int VLC_VAR_VOID ; 
 int /*<<< orphan*/  WaitUnused (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_internals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int (var_SetChecked)(vlc_object_t *p_this, const char *psz_name,
                     int expected_type, vlc_value_t val)
{
    variable_t *p_var;
    vlc_value_t oldval;

    assert( p_this );

    vlc_object_internals_t *p_priv = vlc_internals( p_this );

    p_var = Lookup( p_this, psz_name );
    if( p_var == NULL )
    {
        vlc_mutex_unlock( &p_priv->var_lock );
        return VLC_ENOVAR;
    }

    assert( expected_type == 0 ||
            (p_var->i_type & VLC_VAR_CLASS) == expected_type );
    assert ((p_var->i_type & VLC_VAR_CLASS) != VLC_VAR_VOID);

    WaitUnused( p_this, p_var );

    /* Duplicate data if needed */
    p_var->ops->pf_dup( &val );

    /* Backup needed stuff */
    oldval = p_var->val;

    /* Check boundaries and list */
    CheckValue( p_var, &val );

    /* Set the variable */
    p_var->val = val;

    /* Deal with callbacks */
    TriggerCallback( p_this, p_var, psz_name, oldval );

    /* Free data if needed */
    p_var->ops->pf_free( &oldval );

    vlc_mutex_unlock( &p_priv->var_lock );
    return VLC_SUCCESS;
}