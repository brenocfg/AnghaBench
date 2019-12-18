#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  var_wait; int /*<<< orphan*/  var_lock; } ;
typedef  TYPE_1__ vlc_object_internals_t ;
struct TYPE_7__ {int b_incallback; int /*<<< orphan*/  val; TYPE_3__* value_callbacks; } ;
typedef  TYPE_2__ variable_t ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  p_data; int /*<<< orphan*/  (* pf_value_callback ) (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ callback_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_broadcast (int /*<<< orphan*/ *) ; 
 TYPE_1__* vlc_internals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void TriggerCallback(vlc_object_t *obj, variable_t *var,
                            const char *name, vlc_value_t prev)
{
    assert(obj != NULL);

    callback_entry_t *entry = var->value_callbacks;
    if (entry == NULL)
        return;

    vlc_object_internals_t *priv = vlc_internals(obj);

    assert(!var->b_incallback);
    var->b_incallback = true;
    vlc_mutex_unlock(&priv->var_lock);

    do
    {
        entry->pf_value_callback(obj, name, prev, var->val, entry->p_data);
        entry = entry->next;
    }
    while (entry != NULL);

    vlc_mutex_lock(&priv->var_lock);
    var->b_incallback = false;
    vlc_cond_broadcast(&priv->var_wait);
}