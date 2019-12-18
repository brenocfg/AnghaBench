#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {int /*<<< orphan*/  var_lock; int /*<<< orphan*/  var_root; } ;
typedef  TYPE_1__ vlc_object_internals_t ;
struct TYPE_8__ {scalar_t__ i_usage; int /*<<< orphan*/  b_incallback; } ;
typedef  TYPE_2__ variable_t ;

/* Variables and functions */
 int /*<<< orphan*/  Destroy (TYPE_2__*) ; 
 TYPE_2__* Lookup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  tdelete (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varcmp ; 
 TYPE_1__* vlc_internals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void (var_Destroy)(vlc_object_t *p_this, const char *psz_name)
{
    variable_t *p_var;

    assert( p_this );

    vlc_object_internals_t *p_priv = vlc_internals( p_this );

    p_var = Lookup( p_this, psz_name );
    if( p_var == NULL )
        msg_Dbg( p_this, "attempt to destroy nonexistent variable \"%s\"",
                 psz_name );
    else if( --p_var->i_usage == 0 )
    {
        assert(!p_var->b_incallback);
        tdelete( p_var, &p_priv->var_root, varcmp );
    }
    else
    {
        assert(p_var->i_usage != -1u);
        p_var = NULL;
    }
    vlc_mutex_unlock( &p_priv->var_lock );

    if( p_var != NULL )
        Destroy( p_var );
}