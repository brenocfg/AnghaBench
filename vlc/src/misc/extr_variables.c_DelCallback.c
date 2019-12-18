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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {int /*<<< orphan*/  var_lock; } ;
typedef  TYPE_1__ vlc_object_internals_t ;
typedef  scalar_t__ vlc_callback_type_t ;
struct TYPE_10__ {TYPE_3__* list_callbacks; TYPE_3__* value_callbacks; } ;
typedef  TYPE_2__ variable_t ;
struct TYPE_11__ {scalar_t__ p_data; struct TYPE_11__* next; int /*<<< orphan*/  p_callback; } ;
typedef  TYPE_3__ callback_entry_t ;

/* Variables and functions */
 TYPE_2__* Lookup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  WaitUnused (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* vlc_internals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_value_callback ; 

__attribute__((used)) static void DelCallback( vlc_object_t *p_this, const char *psz_name,
                         const callback_entry_t *restrict match,
                         vlc_callback_type_t i_type )
{
    callback_entry_t **pp, *entry;
    variable_t *p_var;

    assert( p_this );

    vlc_object_internals_t *p_priv = vlc_internals( p_this );

    p_var = Lookup( p_this, psz_name );
    if( p_var == NULL )
    {
        vlc_mutex_unlock( &p_priv->var_lock );
        msg_Err( p_this, "cannot delete callback %p from nonexistent "
                 "variable '%s'", match->p_callback, psz_name );
        return;
    }

    WaitUnused( p_this, p_var );

    if (i_type == vlc_value_callback)
        pp = &p_var->value_callbacks;
    else
        pp = &p_var->list_callbacks;

    entry = *pp;
    assert(entry != NULL);

    while (entry->p_callback != match->p_callback
        || entry->p_data != match->p_data)
    {
        pp = &entry->next;
        entry = *pp;
        assert(entry != NULL);
    }

    *pp = entry->next;
    vlc_mutex_unlock( &p_priv->var_lock );
    free(entry);
}